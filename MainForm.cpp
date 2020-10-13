#include "MainForm.h"
#include "Containers.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <utility>
#include <chrono>
//#include <vld.h> //Debug memmory leaks

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::Collections::Concurrent;
using namespace System::Windows::Forms::DataVisualization::Charting;
using namespace System::Threading;

using PointNT = SorterApp::PointNT; //Точка на грфике зависимости T от N
using Points = SorterApp::Points; //Массив точек PointNT
using NamedPoints = SorterApp::NamedPoints; //Пара точек Points и имени
using PairOfIndexes = SorterApp::PairOfIndexes; //Пара индексов

constexpr double sorting_delay = 100; //Задержка сортировки
constexpr double shuffle_delay = 20; //Задержка перемешивания
constexpr size_t number_columns = 31; //Количество колонок в визуализации сортировок
constexpr size_t number_of_swaps = 2*number_columns; //Количество перестановок при перемешивании
size_t N_graph; //Последнее значение на графике
size_t step; //Шаг с которым меняется n на графике
constexpr double step_size = 0.1; //Величина шага в частях от N_graph
constexpr size_t n0 = 0; //Первое значение на графике
constexpr size_t width_graph_line = 2; //Ширина линии графика
Point start_position_columns; //Начальная позиция, с которой начинают строиться колонки

bool graph_exit = false;

/*--------------------------------------------------------------------------------------------------------------------------------------*/

//Other subsidiary functions
Color ColorFromHSV(double hue, double saturation, double value)
{
    int hi = Convert::ToInt32(Math::Floor(hue / 60)) % 6;
    double f = hue / 60 - Math::Floor(hue / 60);

    value = value * 255;
    int v = Convert::ToInt32(value);
    int p = Convert::ToInt32(value * (1 - saturation));
    int q = Convert::ToInt32(value * (1 - f * saturation));
    int t = Convert::ToInt32(value * (1 - (1 - f) * saturation));

    if (hi == 0)
        return Color::FromArgb(255, v, t, p);
    else if (hi == 1)
        return Color::FromArgb(255, q, v, p);
    else if (hi == 2)
        return Color::FromArgb(255, p, v, t);
    else if (hi == 3)
        return Color::FromArgb(255, p, q, v);
    else if (hi == 4)
        return Color::FromArgb(255, t, p, v);
    else
        return Color::FromArgb(255, v, p, q);
}
//Other subsidiary functions _end

/*--------------------------------------------------------------------------------------------------------------------------------------*/

//Main
[STAThread]
int main(array<String^>^ arg)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    SorterApp::MainForm main_form;
    Application::Run(% main_form);
}
//Main_end

/*--------------------------------------------------------------------------------------------------------------------------------------*/

//Setup
System::Void SorterApp::MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
{
    this->sorters = new std::vector<Containers::Sorter<int>*>{
        new Containers::InsertionSorter<int>{},
        new Containers::ShellSorter<int>{},
        new Containers::QuickSorter<int>{},
        new Containers::BubbleSorter<int>{}
    };
    this->graphs_sorters = new std::vector<Containers::Sorter<int>*>{};
    this->series_named_points = new std::vector<NamedPoints>{ this->sorters->size() };
    for (size_t i = 0; i < this->sorters->size(); i++)
    {
        this->combo_box_sorts->Items->Add(gcnew String(this->sorters->at(i)->Name().c_str()));
        this->selected_sortings->Items->Add(gcnew String(this->sorters->at(i)->Name().c_str()));
        this->selected_sortings->SetItemChecked(i, true);
        this->series_named_points->at(i).second = this->sorters->at(i)->Name();
    }
    if (this->sorters->size())
        this->combo_box_sorts->SelectedItem = this->combo_box_sorts->Items[0];
    for (size_t i = 0; i < number_columns; i++)
    {
        PictureBox^ new_column = gcnew PictureBox();
        new_column->BackColor = Color::Black;
        size_t width_column = (this->page_sorting_visualization->Size.Width - 2 * this->sort_button->Size.Height) / (1.5 * (number_columns - 1) + 1);
        start_position_columns = Point(
            this->combo_box_sorts->Location.X,
            this->combo_box_sorts->Location.Y - this->sort_button->Size.Height - width_column
        );
        size_t difference_height = (start_position_columns.Y - this->sort_button->Size.Height) / number_columns;
        new_column->Location = Point(
            start_position_columns.X + i * (1.5 * width_column), //X
            start_position_columns.Y - i * difference_height     //Y
        );
        new_column->Size = Drawing::Size(width_column, width_column + i * difference_height);
        this->columns.Add(new_column);
        this->page_sorting_visualization->Controls->Add(new_column);
    }
    this->swaps = gcnew List<Point>();
    this->randomizer = gcnew Random();
    this->thread_with_state_shuffling_columns = gcnew Tuple<Thread^, bool>(gcnew Thread(gcnew ThreadStart(this, &SorterApp::MainForm::ShuffleColumns)), true);
    this->thread_with_state_sorting_columns = gcnew Tuple<Thread^, bool>(gcnew Thread(gcnew ThreadStart(this, &SorterApp::MainForm::SortColumns)), true);
    this->thread_build_graph = gcnew Thread(gcnew ThreadStart(this, &SorterApp::MainForm::CreateGraphs));
    this->sequence_int_random = new Containers::ArraySequence<int>{};
}
//Setup_end

/*--------------------------------------------------------------------------------------------------------------------------------------*/

//Menu
System::Void SorterApp::MainForm::MenuSortingVisualizationButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    this->page_home->Visible = false;
    this->page_comparison->Visible = false;
    this->page_sorting_visualization->Visible = true;
    this->menu_sorting_visualization_button->BackColor = Color::MediumSeaGreen; //Показываем цветом активность кнопки
    this->menu_comparison_button->BackColor = Color::FromArgb(219, 199, 172); //Показываем цветом не активность кнопки
}
System::Void SorterApp::MainForm::MenuComparisonButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    this->page_home->Visible = false;
    this->page_sorting_visualization->Visible = false;
    this->page_comparison->Visible = true;
    this->menu_sorting_visualization_button->BackColor = Color::FromArgb(219, 199, 172); //Показываем цветом не активность кнопки
    this->menu_comparison_button->BackColor = Color::MediumSeaGreen; //Показываем цветом активность кнопки
}
System::Void SorterApp::MainForm::Heading_Click(System::Object^ sender, System::EventArgs^ e)
{
    this->page_sorting_visualization->Visible = false;
    this->page_comparison->Visible = false;
    this->page_home->Visible = true;
    this->menu_sorting_visualization_button->BackColor = Color::FromArgb(219, 199, 172); //Показываем цветом не активность кнопки
    this->menu_comparison_button->BackColor = Color::FromArgb(219, 199, 172); //Показываем цветом не активность кнопки
}
System::Void SorterApp::MainForm::Logo_Click(System::Object^ sender, System::EventArgs^ e)
{
    this->page_sorting_visualization->Visible = false;
    this->page_comparison->Visible = false;
    this->page_home->Visible = true;
    this->menu_sorting_visualization_button->BackColor = Color::FromArgb(219, 199, 172); //Показываем цветом не активность кнопки
    this->menu_comparison_button->BackColor = Color::FromArgb(219, 199, 172); //Показываем цветом не активность кнопки
}
//Menu_end

/*--------------------------------------------------------------------------------------------------------------------------------------*/

//Buttons

//SortButton
System::Void SorterApp::MainForm::SortButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (this->thread_with_state_shuffling_columns->Item1->ThreadState == ThreadState::Running)
    {
        //Делаем поток не активным
        this->thread_with_state_shuffling_columns = gcnew Tuple<Thread^, bool>(this->thread_with_state_shuffling_columns->Item1, false);
        return;
    }
    if (this->thread_with_state_sorting_columns->Item1->ThreadState == ThreadState::Running)
    {
        //Делаем поток не активным
        this->thread_with_state_sorting_columns = gcnew Tuple<Thread^, bool>(this->thread_with_state_sorting_columns->Item1, false);
        return;
    }
    //Создаем поток и делаем его активным
    if (this->thread_with_state_sorting_columns->Item1->ThreadState == ThreadState::Stopped)
        this->thread_with_state_sorting_columns = gcnew Tuple<Thread^, bool>(gcnew Thread(gcnew ThreadStart(this, &SorterApp::MainForm::SortColumns)), true);
    this->thread_with_state_sorting_columns->Item1->Start();
}
//SortButton_end
//ShuffleButton
System::Void SorterApp::MainForm::ShuffleButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (this->thread_with_state_shuffling_columns->Item1->ThreadState == ThreadState::Running)
    {
        //Делаем поток не активным
        this->thread_with_state_shuffling_columns = gcnew Tuple<Thread^, bool>(this->thread_with_state_shuffling_columns->Item1, false);
        return;
    }
    if (this->thread_with_state_sorting_columns->Item1->ThreadState == ThreadState::Running)
    {
        //Делаем поток не активным
        this->thread_with_state_sorting_columns = gcnew Tuple<Thread^, bool>(this->thread_with_state_sorting_columns->Item1, false);
        return;
    }
    //Создаем поток и делаем его активным
    if (this->thread_with_state_shuffling_columns->Item1->ThreadState == ThreadState::Stopped)
        this->thread_with_state_shuffling_columns = gcnew Tuple<Thread^, bool>(gcnew Thread(gcnew ThreadStart(this, &SorterApp::MainForm::ShuffleColumns)), true);
    this->thread_with_state_shuffling_columns->Item1->Start();
}
//ShuffleButton_end
//BuildGraphsButton
System::Void SorterApp::MainForm::BuildGraphsButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (this->thread_build_graph->ThreadState == ThreadState::Running)
    {
        this->progress_bar->Value = 0;
        return;
    }
    if (this->thread_build_graph->ThreadState == ThreadState::Stopped)
        this->thread_build_graph = gcnew Thread(gcnew ThreadStart(this, &SorterApp::MainForm::CreateGraphs));
    if (this->thread_build_graph->ThreadState == ThreadState::Unstarted)
    {
        N_graph = System::Decimal::ToUInt32(this->N_graph_numeric_up_down->Value);
        step = N_graph * step_size;
        for (auto sort : *this->graphs_sorters)
            delete sort;
        this->graphs_sorters->clear();
        for (size_t i = 0; i < this->selected_sortings->CheckedItems->Count; i++)
            this->graphs_sorters->push_back(this->sorters->at(this->selected_sortings->CheckedIndices[i])->Clone());
        this->chart->Series->Clear();
        this->progress_bar->Value = 0;
        this->progress_bar->Minimum = 0;
        this->progress_bar->Maximum = (int((N_graph - n0) / step) + 1) * this->graphs_sorters->size();
        this->series_named_points->clear();
        this->series_named_points->resize(this->graphs_sorters->size());
        for (size_t i = 0; i < this->graphs_sorters->size(); i++)
        {
            this->series_named_points->at(i).second = this->graphs_sorters->at(i)->Name();
            this->series_named_points->at(i).first.resize(int((N_graph - n0) / step) + 1);
        }
        if (step != 0 && !this->graphs_sorters->empty())
        {
            for (size_t i = 0; i < N_graph; i++)
                this->sequence_int_random->Append(this->randomizer->Next(INT_MIN, INT_MAX));
            this->thread_build_graph->Start();
        }
    }
}
//BuildGraphsButton_end

//Buttons_end

/*--------------------------------------------------------------------------------------------------------------------------------------*/

//Executable code

//Shuffle and Sort columns
void SorterApp::MainForm::SwapColumns(size_t i, size_t j, double delay)
{
    if (i == j)
        return;
    this->columns[i]->BackColor = Color::Red;
    this->columns[j]->BackColor = Color::Red;
    this->page_sorting_visualization->Update();
    Sleep(delay);
    this->columns[i]->BackColor = Color::Black;
    this->columns[j]->BackColor = Color::Black;
    int buffer = this->columns[i]->Location.X;
    this->columns[i]->Location = Point(this->columns[j]->Location.X, this->columns[i]->Location.Y);
    this->columns[j]->Location = Point(buffer, this->columns[j]->Location.Y);
    this->page_sorting_visualization->Update();
}
void SorterApp::MainForm::SortColumns()
{
    std::vector<Containers::Sorter<int>*> sorters_copy;
    for (auto sort : *this->sorters)
        sorters_copy.push_back(sort->Clone());
    Containers::ArraySequence<int> heights;
    for (size_t i = 0; i < this->columns.Count; i++)
        heights.Append(this->columns[i]->Size.Height);
    Containers::Sorter<int>* selected_sorter = sorters_copy[this->combo_box_sorts->SelectedIndex];
    selected_sorter->SortWithSwaps(heights); //Сортируем heights
    std::vector<std::pair<size_t, size_t>> swaps = selected_sorter->GetSwaps();
    for (auto sort : sorters_copy)
        delete sort;
    this->swaps->Clear();
    for (auto pair_of_indexes : swaps)
        this->swaps->Add(PairOfIndexes(pair_of_indexes.first, pair_of_indexes.second));
    for (size_t i = 0; i < this->swaps->Count; i++)
    {
        size_t first_index = this->swaps[i].X;
        size_t second_index = this->swaps[i].Y;
        this->SwapColumns(first_index, second_index, sorting_delay);
        PictureBox^ buffer = this->columns[first_index];
        this->columns[first_index] = this->columns[second_index];
        this->columns[second_index] = buffer;
        if (this->thread_with_state_sorting_columns->Item2 == false)
            this->thread_with_state_sorting_columns->Item1->Abort(); //Принудительно завершаем поток
    }
}
void SorterApp::MainForm::ShuffleColumns()
{
    for (size_t i = 0; i < number_of_swaps; i++)
    {
        size_t j = this->randomizer->Next(0, this->columns.Count);
        size_t k = this->randomizer->Next(0, this->columns.Count);
        if (j == k)
        {
            j = (j == this->columns.Count - 1) ? j - 1 : j + 1;
        }
        SwapColumns(j, k, shuffle_delay);
        PictureBox^ buffer = this->columns[j];
        this->columns[j] = this->columns[k];
        this->columns[k] = buffer;
        if (this->thread_with_state_shuffling_columns->Item2 == false)
            this->thread_with_state_shuffling_columns->Item1->Abort(); //Принудительно завершаем поток
    }
}
//Shuffle and Sort columns _end
//Create graphs
void SorterApp::MainForm::CreateGraphs()
{
    Tasks::Parallel::For(0, this->progress_bar->Maximum, gcnew Action<int>(this, &SorterApp::MainForm::CreatePointOnGraph));
    for (size_t i = 0; i < this->series_named_points->size(); i++)
    {
        Dictionary<double, double> points;
        for (size_t j = 0; j < this->series_named_points->at(i).first.size(); j++)
            points.Add(
                this->series_named_points->at(i).first[j].first,
                this->series_named_points->at(i).first[j].second
            );
        Series^ new_series = gcnew Series();
        new_series->ChartType = SeriesChartType::Spline;
        new_series->Points->DataBindXY(points.Keys, points.Values);
        new_series->Color = ColorFromHSV(i * 360 / this->series_named_points->size(), 1, 1);
        new_series->BorderWidth = width_graph_line;
        new_series->Name = gcnew String(this->series_named_points->at(i).second.c_str());
        this->chart->Series->Add(new_series);
    }
    this->chart->ChartAreas[0]->AxisX->Maximum = N_graph;
    size_t max_series_value = 0;
    for (size_t i = 0; i < this->chart->Series->Count; i++)
    {
        size_t current_max_value = this->chart->Series[i]->Points->FindMaxByValue()->YValues[0];
        max_series_value = max(max_series_value, current_max_value);
    }
    this->chart->ChartAreas[0]->AxisY->Maximum = max_series_value;
}
void SorterApp::MainForm::CreatePointOnGraph(int i)
{
    int n = n0 + int(i / this->graphs_sorters->size()) * step;
    int j = i % this->graphs_sorters->size();
    Containers::Sorter<int>* current_sorter = this->graphs_sorters->at(j)->Clone();
    Containers::Sequence<int>* buffer_sequence = this->sequence_int_random->GetSubsequence(0, n);
    auto start = std::chrono::high_resolution_clock::now();
    current_sorter->SortWithExecution(*buffer_sequence, graph_exit);
    auto end = std::chrono::high_resolution_clock::now();
    delete buffer_sequence;
    delete current_sorter;
    long long operating_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    this->series_named_points->at(j).first[int((n - n0) / step)] = PointNT(n, operating_time);
    Monitor::Enter(this);
    this->progress_bar->Value++;
    Monitor::Exit(this);
}
//Create graphs _end

//Executable code _end

/*--------------------------------------------------------------------------------------------------------------------------------------*/

//Closed
System::Void SorterApp::MainForm::MainForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
{
    for (auto sort : *this->sorters)
        delete sort;
    delete this->sorters;
    for (auto sort : *this->graphs_sorters)
        delete sort;
    delete this->graphs_sorters;
    delete this->series_named_points;
    delete this->sequence_int_random;
}
//Closed_end