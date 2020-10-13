#pragma once
#include"Containers.h"
#include<vector>
#include<utility>
#include<string>

namespace SorterApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	using PointNT = std::pair<int, int>;
	using Points = std::vector<PointNT>;
	using NamedPoints = std::pair<Points, std::string>;
	using PairOfIndexes = Point;

	/// <summary>
	/// —водка дл€ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: Containers::Sequence<int>* sequence_int_random;
	private: std::vector<NamedPoints>* series_named_points;
	private: std::vector<Containers::Sorter<int>*>* sorters;
	private: std::vector<Containers::Sorter<int>*>* graphs_sorters;
	private: Random^ randomizer;
	private: Thread^ thread_build_graph;
	private: Tuple<Thread^, bool>^ thread_with_state_sorting_columns;
	private: Tuple<Thread^, bool>^ thread_with_state_shuffling_columns;
	private: Generic::List<PairOfIndexes>^ swaps;
	private: Generic::List<PictureBox^> columns;
	private: System::Windows::Forms::PictureBox^ board;
	private: System::Windows::Forms::Button^ menu_sorting_visualization_button;
	private: System::Windows::Forms::Label^ heading;
	private: System::Windows::Forms::PictureBox^ logo;
	private: System::Windows::Forms::Button^ menu_comparison_button;
	private: System::Windows::Forms::Label^ speech_label;
	private: System::Windows::Forms::PictureBox^ peace_img;
	private: System::Windows::Forms::PictureBox^ underline;
	private: System::Windows::Forms::Panel^ page_home;
	private: System::Windows::Forms::Panel^ page_comparison;
	private: System::Windows::Forms::Button^ sort_button;
	private: System::Windows::Forms::Button^ shuffle_button;
	private: System::Windows::Forms::ComboBox^ combo_box_sorts;
	private: System::Windows::Forms::Panel^ page_sorting_visualization;
	private: System::Windows::Forms::Button^ build_graphs_button;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart;
	private: System::Windows::Forms::ProgressBar^ progress_bar;
	private: System::Windows::Forms::Label^ loading_label;
	private: System::Windows::Forms::Label^ N_label;
	private: System::Windows::Forms::NumericUpDown^ N_graph_numeric_up_down;
	private: System::Windows::Forms::CheckedListBox^ selected_sortings;



	private: System::ComponentModel::IContainer^ components;
		   /// <summary>
		   /// ќб€зательна€ переменна€ конструктора.
		   /// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			   System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			   this->board = (gcnew System::Windows::Forms::PictureBox());
			   this->menu_sorting_visualization_button = (gcnew System::Windows::Forms::Button());
			   this->heading = (gcnew System::Windows::Forms::Label());
			   this->logo = (gcnew System::Windows::Forms::PictureBox());
			   this->menu_comparison_button = (gcnew System::Windows::Forms::Button());
			   this->speech_label = (gcnew System::Windows::Forms::Label());
			   this->peace_img = (gcnew System::Windows::Forms::PictureBox());
			   this->underline = (gcnew System::Windows::Forms::PictureBox());
			   this->page_home = (gcnew System::Windows::Forms::Panel());
			   this->page_comparison = (gcnew System::Windows::Forms::Panel());
			   this->selected_sortings = (gcnew System::Windows::Forms::CheckedListBox());
			   this->N_label = (gcnew System::Windows::Forms::Label());
			   this->N_graph_numeric_up_down = (gcnew System::Windows::Forms::NumericUpDown());
			   this->loading_label = (gcnew System::Windows::Forms::Label());
			   this->progress_bar = (gcnew System::Windows::Forms::ProgressBar());
			   this->build_graphs_button = (gcnew System::Windows::Forms::Button());
			   this->chart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			   this->page_sorting_visualization = (gcnew System::Windows::Forms::Panel());
			   this->combo_box_sorts = (gcnew System::Windows::Forms::ComboBox());
			   this->shuffle_button = (gcnew System::Windows::Forms::Button());
			   this->sort_button = (gcnew System::Windows::Forms::Button());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->board))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->logo))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->peace_img))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->underline))->BeginInit();
			   this->page_home->SuspendLayout();
			   this->page_comparison->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->N_graph_numeric_up_down))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart))->BeginInit();
			   this->page_sorting_visualization->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // board
			   // 
			   this->board->Dock = System::Windows::Forms::DockStyle::Left;
			   this->board->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"board.Image")));
			   this->board->Location = System::Drawing::Point(0, 0);
			   this->board->Name = L"board";
			   this->board->Size = System::Drawing::Size(295, 729);
			   this->board->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->board->TabIndex = 0;
			   this->board->TabStop = false;
			   // 
			   // menu_sorting_visualization_button
			   // 
			   this->menu_sorting_visualization_button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(219)),
				   static_cast<System::Int32>(static_cast<System::Byte>(199)), static_cast<System::Int32>(static_cast<System::Byte>(172)));
			   this->menu_sorting_visualization_button->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->menu_sorting_visualization_button->FlatAppearance->BorderColor = System::Drawing::Color::MediumSeaGreen;
			   this->menu_sorting_visualization_button->FlatAppearance->BorderSize = 3;
			   this->menu_sorting_visualization_button->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MediumSeaGreen;
			   this->menu_sorting_visualization_button->FlatAppearance->MouseOverBackColor = System::Drawing::Color::MediumSeaGreen;
			   this->menu_sorting_visualization_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->menu_sorting_visualization_button->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 12, System::Drawing::FontStyle::Regular,
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			   this->menu_sorting_visualization_button->ForeColor = System::Drawing::Color::LemonChiffon;
			   this->menu_sorting_visualization_button->Location = System::Drawing::Point(35, 120);
			   this->menu_sorting_visualization_button->Name = L"menu_sorting_visualization_button";
			   this->menu_sorting_visualization_button->Size = System::Drawing::Size(180, 50);
			   this->menu_sorting_visualization_button->TabIndex = 1;
			   this->menu_sorting_visualization_button->Text = L"Sorting visualization";
			   this->menu_sorting_visualization_button->UseVisualStyleBackColor = false;
			   this->menu_sorting_visualization_button->Click += gcnew System::EventHandler(this, &MainForm::MenuSortingVisualizationButton_Click);
			   // 
			   // heading
			   // 
			   this->heading->AutoSize = true;
			   this->heading->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(219)), static_cast<System::Int32>(static_cast<System::Byte>(199)),
				   static_cast<System::Int32>(static_cast<System::Byte>(172)));
			   this->heading->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->heading->Font = (gcnew System::Drawing::Font(L"Lucida Sans Typewriter", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->heading->ForeColor = System::Drawing::Color::DarkGreen;
			   this->heading->Location = System::Drawing::Point(72, 37);
			   this->heading->Name = L"heading";
			   this->heading->Size = System::Drawing::Size(143, 39);
			   this->heading->TabIndex = 2;
			   this->heading->Text = L"Sorter";
			   this->heading->Click += gcnew System::EventHandler(this, &MainForm::Heading_Click);
			   // 
			   // logo
			   // 
			   this->logo->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(219)), static_cast<System::Int32>(static_cast<System::Byte>(199)),
				   static_cast<System::Int32>(static_cast<System::Byte>(172)));
			   this->logo->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->logo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"logo.Image")));
			   this->logo->Location = System::Drawing::Point(35, 37);
			   this->logo->Name = L"logo";
			   this->logo->Size = System::Drawing::Size(40, 39);
			   this->logo->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->logo->TabIndex = 3;
			   this->logo->TabStop = false;
			   this->logo->Click += gcnew System::EventHandler(this, &MainForm::Logo_Click);
			   // 
			   // menu_comparison_button
			   // 
			   this->menu_comparison_button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(219)),
				   static_cast<System::Int32>(static_cast<System::Byte>(199)), static_cast<System::Int32>(static_cast<System::Byte>(172)));
			   this->menu_comparison_button->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->menu_comparison_button->FlatAppearance->BorderColor = System::Drawing::Color::MediumSeaGreen;
			   this->menu_comparison_button->FlatAppearance->BorderSize = 3;
			   this->menu_comparison_button->FlatAppearance->MouseDownBackColor = System::Drawing::Color::MediumSeaGreen;
			   this->menu_comparison_button->FlatAppearance->MouseOverBackColor = System::Drawing::Color::MediumSeaGreen;
			   this->menu_comparison_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->menu_comparison_button->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->menu_comparison_button->ForeColor = System::Drawing::Color::LemonChiffon;
			   this->menu_comparison_button->Location = System::Drawing::Point(35, 195);
			   this->menu_comparison_button->Name = L"menu_comparison_button";
			   this->menu_comparison_button->Size = System::Drawing::Size(180, 50);
			   this->menu_comparison_button->TabIndex = 4;
			   this->menu_comparison_button->Text = L"Comparison of sorts";
			   this->menu_comparison_button->UseVisualStyleBackColor = false;
			   this->menu_comparison_button->Click += gcnew System::EventHandler(this, &MainForm::MenuComparisonButton_Click);
			   // 
			   // speech_label
			   // 
			   this->speech_label->AutoSize = true;
			   this->speech_label->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->speech_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(39)),
				   static_cast<System::Int32>(static_cast<System::Byte>(107)));
			   this->speech_label->Location = System::Drawing::Point(29, 480);
			   this->speech_label->Name = L"speech_label";
			   this->speech_label->Size = System::Drawing::Size(627, 135);
			   this->speech_label->TabIndex = 5;
			   this->speech_label->Text = resources->GetString(L"speech_label.Text");
			   this->speech_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // peace_img
			   // 
			   this->peace_img->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"peace_img.Image")));
			   this->peace_img->Location = System::Drawing::Point(187, 92);
			   this->peace_img->Name = L"peace_img";
			   this->peace_img->Size = System::Drawing::Size(311, 317);
			   this->peace_img->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->peace_img->TabIndex = 10;
			   this->peace_img->TabStop = false;
			   // 
			   // underline
			   // 
			   this->underline->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(219)), static_cast<System::Int32>(static_cast<System::Byte>(199)),
				   static_cast<System::Int32>(static_cast<System::Byte>(172)));
			   this->underline->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"underline.Image")));
			   this->underline->Location = System::Drawing::Point(35, 92);
			   this->underline->Name = L"underline";
			   this->underline->Size = System::Drawing::Size(180, 2);
			   this->underline->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->underline->TabIndex = 7;
			   this->underline->TabStop = false;
			   // 
			   // page_home
			   // 
			   this->page_home->Controls->Add(this->peace_img);
			   this->page_home->Controls->Add(this->speech_label);
			   this->page_home->Dock = System::Windows::Forms::DockStyle::Right;
			   this->page_home->Location = System::Drawing::Point(295, 0);
			   this->page_home->Name = L"page_home";
			   this->page_home->Size = System::Drawing::Size(713, 729);
			   this->page_home->TabIndex = 11;
			   // 
			   // page_comparison
			   // 
			   this->page_comparison->Controls->Add(this->selected_sortings);
			   this->page_comparison->Controls->Add(this->N_label);
			   this->page_comparison->Controls->Add(this->N_graph_numeric_up_down);
			   this->page_comparison->Controls->Add(this->loading_label);
			   this->page_comparison->Controls->Add(this->progress_bar);
			   this->page_comparison->Controls->Add(this->build_graphs_button);
			   this->page_comparison->Controls->Add(this->chart);
			   this->page_comparison->Location = System::Drawing::Point(295, 0);
			   this->page_comparison->Name = L"page_comparison";
			   this->page_comparison->Size = System::Drawing::Size(713, 729);
			   this->page_comparison->TabIndex = 0;
			   this->page_comparison->Visible = false;
			   // 
			   // selected_sortings
			   // 
			   this->selected_sortings->BackColor = System::Drawing::Color::MediumSeaGreen;
			   this->selected_sortings->BorderStyle = System::Windows::Forms::BorderStyle::None;
			   this->selected_sortings->CheckOnClick = true;
			   this->selected_sortings->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->selected_sortings->ForeColor = System::Drawing::Color::LemonChiffon;
			   this->selected_sortings->FormattingEnabled = true;
			   this->selected_sortings->Location = System::Drawing::Point(242, 653);
			   this->selected_sortings->Name = L"selected_sortings";
			   this->selected_sortings->Size = System::Drawing::Size(180, 26);
			   this->selected_sortings->TabIndex = 17;
			   // 
			   // N_label
			   // 
			   this->N_label->AutoSize = true;
			   this->N_label->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->N_label->ForeColor = System::Drawing::Color::MediumSeaGreen;
			   this->N_label->Location = System::Drawing::Point(96, 628);
			   this->N_label->Name = L"N_label";
			   this->N_label->Size = System::Drawing::Size(21, 18);
			   this->N_label->TabIndex = 16;
			   this->N_label->Text = L"N";
			   this->N_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // N_graph_numeric_up_down
			   // 
			   this->N_graph_numeric_up_down->BackColor = System::Drawing::Color::MediumSeaGreen;
			   this->N_graph_numeric_up_down->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->N_graph_numeric_up_down->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->N_graph_numeric_up_down->ForeColor = System::Drawing::Color::LemonChiffon;
			   this->N_graph_numeric_up_down->Location = System::Drawing::Point(23, 649);
			   this->N_graph_numeric_up_down->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 500000, 0, 0, 0 });
			   this->N_graph_numeric_up_down->Name = L"N_graph_numeric_up_down";
			   this->N_graph_numeric_up_down->Size = System::Drawing::Size(180, 30);
			   this->N_graph_numeric_up_down->TabIndex = 15;
			   this->N_graph_numeric_up_down->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			   this->N_graph_numeric_up_down->ThousandsSeparator = true;
			   this->N_graph_numeric_up_down->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5000, 0, 0, 0 });
			   // 
			   // loading_label
			   // 
			   this->loading_label->AutoSize = true;
			   this->loading_label->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->loading_label->ForeColor = System::Drawing::Color::MediumSeaGreen;
			   this->loading_label->Location = System::Drawing::Point(292, 555);
			   this->loading_label->Name = L"loading_label";
			   this->loading_label->Size = System::Drawing::Size(71, 18);
			   this->loading_label->TabIndex = 14;
			   this->loading_label->Text = L"Loading";
			   this->loading_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // progress_bar
			   // 
			   this->progress_bar->ForeColor = System::Drawing::Color::MediumSeaGreen;
			   this->progress_bar->Location = System::Drawing::Point(23, 576);
			   this->progress_bar->Name = L"progress_bar";
			   this->progress_bar->Size = System::Drawing::Size(623, 28);
			   this->progress_bar->TabIndex = 13;
			   // 
			   // build_graphs_button
			   // 
			   this->build_graphs_button->BackColor = System::Drawing::Color::MediumSeaGreen;
			   this->build_graphs_button->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->build_graphs_button->FlatAppearance->BorderColor = System::Drawing::Color::MediumSeaGreen;
			   this->build_graphs_button->FlatAppearance->BorderSize = 0;
			   this->build_graphs_button->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DarkGreen;
			   this->build_graphs_button->FlatAppearance->MouseOverBackColor = System::Drawing::Color::DarkGreen;
			   this->build_graphs_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->build_graphs_button->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->build_graphs_button->ForeColor = System::Drawing::Color::LemonChiffon;
			   this->build_graphs_button->Location = System::Drawing::Point(466, 629);
			   this->build_graphs_button->Name = L"build_graphs_button";
			   this->build_graphs_button->Size = System::Drawing::Size(180, 50);
			   this->build_graphs_button->TabIndex = 12;
			   this->build_graphs_button->Text = L"Build graphs";
			   this->build_graphs_button->UseVisualStyleBackColor = false;
			   this->build_graphs_button->Click += gcnew System::EventHandler(this, &MainForm::BuildGraphsButton_Click);
			   // 
			   // chart
			   // 
			   this->chart->BackColor = System::Drawing::Color::MediumSeaGreen;
			   chartArea1->AxisX->ArrowStyle = System::Windows::Forms::DataVisualization::Charting::AxisArrowStyle::SharpTriangle;
			   chartArea1->AxisX->IsLabelAutoFit = false;
			   chartArea1->AxisX->IsMarginVisible = false;
			   chartArea1->AxisX->LabelStyle->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   chartArea1->AxisX->LabelStyle->ForeColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisX->LineColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisX->MajorGrid->LineColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisX->MajorTickMark->LineColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisX->MajorTickMark->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::NotSet;
			   chartArea1->AxisX->MinorGrid->LineColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisX->MinorTickMark->LineColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisX->ScaleView->Zoomable = false;
			   chartArea1->AxisX->Title = L"N";
			   chartArea1->AxisX->TitleAlignment = System::Drawing::StringAlignment::Far;
			   chartArea1->AxisX->TitleFont = (gcnew System::Drawing::Font(L"Lucida Sans", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   chartArea1->AxisX->TitleForeColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisY->ArrowStyle = System::Windows::Forms::DataVisualization::Charting::AxisArrowStyle::SharpTriangle;
			   chartArea1->AxisY->IsLabelAutoFit = false;
			   chartArea1->AxisY->IsMarginVisible = false;
			   chartArea1->AxisY->LabelStyle->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   chartArea1->AxisY->LabelStyle->ForeColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisY->LineColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisY->MajorGrid->LineColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisY->MajorTickMark->LineColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisY->MinorGrid->LineColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisY->MinorTickMark->LineColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->AxisY->ScaleView->Zoomable = false;
			   chartArea1->AxisY->Title = L"time (ms)";
			   chartArea1->AxisY->TitleAlignment = System::Drawing::StringAlignment::Far;
			   chartArea1->AxisY->TitleFont = (gcnew System::Drawing::Font(L"Lucida Sans", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   chartArea1->AxisY->TitleForeColor = System::Drawing::Color::LemonChiffon;
			   chartArea1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(219)), static_cast<System::Int32>(static_cast<System::Byte>(199)),
				   static_cast<System::Int32>(static_cast<System::Byte>(172)));
			   chartArea1->Name = L"chart_area";
			   this->chart->ChartAreas->Add(chartArea1);
			   legend1->BackColor = System::Drawing::Color::MediumSeaGreen;
			   legend1->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			   legend1->Font = (gcnew System::Drawing::Font(L"Lucida Sans Typewriter", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   legend1->ForeColor = System::Drawing::Color::LemonChiffon;
			   legend1->IsTextAutoFit = false;
			   legend1->LegendStyle = System::Windows::Forms::DataVisualization::Charting::LegendStyle::Row;
			   legend1->Name = L"legend";
			   legend1->TableStyle = System::Windows::Forms::DataVisualization::Charting::LegendTableStyle::Tall;
			   this->chart->Legends->Add(legend1);
			   this->chart->Location = System::Drawing::Point(23, 37);
			   this->chart->Name = L"chart";
			   this->chart->Size = System::Drawing::Size(623, 483);
			   this->chart->TabIndex = 0;
			   this->chart->Text = L"chart";
			   // 
			   // page_sorting_visualization
			   // 
			   this->page_sorting_visualization->Controls->Add(this->combo_box_sorts);
			   this->page_sorting_visualization->Controls->Add(this->shuffle_button);
			   this->page_sorting_visualization->Controls->Add(this->sort_button);
			   this->page_sorting_visualization->Location = System::Drawing::Point(255, 0);
			   this->page_sorting_visualization->Name = L"page_sorting_visualization";
			   this->page_sorting_visualization->Size = System::Drawing::Size(753, 729);
			   this->page_sorting_visualization->TabIndex = 11;
			   this->page_sorting_visualization->Visible = false;
			   // 
			   // combo_box_sorts
			   // 
			   this->combo_box_sorts->BackColor = System::Drawing::Color::MediumSeaGreen;
			   this->combo_box_sorts->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->combo_box_sorts->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			   this->combo_box_sorts->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->combo_box_sorts->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->combo_box_sorts->ForeColor = System::Drawing::Color::LemonChiffon;
			   this->combo_box_sorts->FormattingEnabled = true;
			   this->combo_box_sorts->ItemHeight = 18;
			   this->combo_box_sorts->Location = System::Drawing::Point(50, 554);
			   this->combo_box_sorts->Name = L"combo_box_sorts";
			   this->combo_box_sorts->Size = System::Drawing::Size(180, 26);
			   this->combo_box_sorts->TabIndex = 2;
			   // 
			   // shuffle_button
			   // 
			   this->shuffle_button->BackColor = System::Drawing::Color::MediumSeaGreen;
			   this->shuffle_button->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->shuffle_button->FlatAppearance->BorderSize = 0;
			   this->shuffle_button->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DarkGreen;
			   this->shuffle_button->FlatAppearance->MouseOverBackColor = System::Drawing::Color::DarkGreen;
			   this->shuffle_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->shuffle_button->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->shuffle_button->ForeColor = System::Drawing::Color::LemonChiffon;
			   this->shuffle_button->Location = System::Drawing::Point(524, 554);
			   this->shuffle_button->Name = L"shuffle_button";
			   this->shuffle_button->Size = System::Drawing::Size(180, 50);
			   this->shuffle_button->TabIndex = 1;
			   this->shuffle_button->Text = L"Shuffle";
			   this->shuffle_button->UseVisualStyleBackColor = false;
			   this->shuffle_button->Click += gcnew System::EventHandler(this, &MainForm::ShuffleButton_Click);
			   // 
			   // sort_button
			   // 
			   this->sort_button->BackColor = System::Drawing::Color::MediumSeaGreen;
			   this->sort_button->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->sort_button->FlatAppearance->BorderSize = 0;
			   this->sort_button->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DarkGreen;
			   this->sort_button->FlatAppearance->MouseOverBackColor = System::Drawing::Color::DarkGreen;
			   this->sort_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->sort_button->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->sort_button->ForeColor = System::Drawing::Color::LemonChiffon;
			   this->sort_button->Location = System::Drawing::Point(524, 629);
			   this->sort_button->Name = L"sort_button";
			   this->sort_button->Size = System::Drawing::Size(180, 50);
			   this->sort_button->TabIndex = 0;
			   this->sort_button->Text = L"Sort";
			   this->sort_button->UseVisualStyleBackColor = false;
			   this->sort_button->Click += gcnew System::EventHandler(this, &MainForm::SortButton_Click);
			   // 
			   // MainForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			   this->ClientSize = System::Drawing::Size(1008, 729);
			   this->Controls->Add(this->underline);
			   this->Controls->Add(this->heading);
			   this->Controls->Add(this->logo);
			   this->Controls->Add(this->menu_sorting_visualization_button);
			   this->Controls->Add(this->menu_comparison_button);
			   this->Controls->Add(this->board);
			   this->Controls->Add(this->page_comparison);
			   this->Controls->Add(this->page_home);
			   this->Controls->Add(this->page_sorting_visualization);
			   this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			   this->MaximizeBox = false;
			   this->Name = L"MainForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Sorter";
			   this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
			   this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->board))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->logo))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->peace_img))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->underline))->EndInit();
			   this->page_home->ResumeLayout(false);
			   this->page_home->PerformLayout();
			   this->page_comparison->ResumeLayout(false);
			   this->page_comparison->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->N_graph_numeric_up_down))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart))->EndInit();
			   this->page_sorting_visualization->ResumeLayout(false);
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: void SwapColumns(size_t i, size_t j, double delay);
	private: void SortColumns();
	private: void ShuffleColumns();
	private: void CreateGraphs();
	private: void CreatePointOnGraph(int i);
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MenuSortingVisualizationButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MenuComparisonButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Heading_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Logo_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void SortButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ShuffleButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void BuildGraphsButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MainForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);

};
}
