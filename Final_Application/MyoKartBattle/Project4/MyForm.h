#pragma once

#include <iostream>
#include <iomanip>
#include <stdexcept>
namespace Project4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		bool startCalibrating;
	private: System::Windows::Forms::ComboBox^  comPortSelector2;
	public:

	public:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;


	public:	MyForm(void)
		{
			InitializeComponent();


			//TODO: Make this a nice funtion.
			this->comPortSelector->Items->Clear();
			array<String^>^ serialPorts = nullptr;
			serialPorts = this->serialPortToDevice->GetPortNames();
			for each(String^ port in serialPorts)
			{
				this->comPortSelector->Items->Add(port);
			}

			this->comPortSelector2->Items->Clear();
			serialPorts = nullptr;
			serialPorts = this->serialPortToDevice2->GetPortNames();
			for each(String^ port in serialPorts)
			{
				this->comPortSelector2->Items->Add(port);
			}

		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (this->serialPortToDevice->IsOpen) {
				this->serialPortToDevice->Close();
			}

			if (this->serialPortToDevice2->IsOpen) {
				this->serialPortToDevice2->Close();
			}

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  comPortSelector;
	protected:

	protected:

	private: System::IO::Ports::SerialPort^  serialPortToDevice;
	private: System::IO::Ports::SerialPort^  serialPortToDevice2;
	private: System::Windows::Forms::Button^  connectButton;
	protected:


	private: System::Windows::Forms::Button^  button2;

	private: System::ComponentModel::IContainer^  components;




	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
	public: bool LockingEnalbed = true;

#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void)
			{
				this->components = (gcnew System::ComponentModel::Container());
				System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
				this->comPortSelector = (gcnew System::Windows::Forms::ComboBox());
				this->serialPortToDevice = (gcnew System::IO::Ports::SerialPort(this->components));
				this->serialPortToDevice2 = (gcnew System::IO::Ports::SerialPort(this->components));
				this->connectButton = (gcnew System::Windows::Forms::Button());
				this->button2 = (gcnew System::Windows::Forms::Button());
				this->comPortSelector2 = (gcnew System::Windows::Forms::ComboBox());
				this->label1 = (gcnew System::Windows::Forms::Label());
				this->label2 = (gcnew System::Windows::Forms::Label());
				this->SuspendLayout();
				// 
				// comPortSelector
				// 
				this->comPortSelector->FormattingEnabled = true;
				this->comPortSelector->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"Select COM Port" });
				this->comPortSelector->Location = System::Drawing::Point(87, 45);
				this->comPortSelector->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
				this->comPortSelector->Name = L"comPortSelector";
				this->comPortSelector->Size = System::Drawing::Size(266, 28);
				this->comPortSelector->TabIndex = 0;
				this->comPortSelector->Text = L"Select COM Port";
				this->comPortSelector->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comPortSelector_SelectedIndexChanged);
				// 
				// serialPortToDevice
				// 
				this->serialPortToDevice->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &MyForm::serialPortToDevice_DataReceived);
				this->serialPortToDevice2->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &MyForm::serialPortToDevice_DataReceived2);
				
				// 
				// connectButton
				// 
				this->connectButton->Location = System::Drawing::Point(179, 155);
				this->connectButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
				this->connectButton->Name = L"connectButton";
				this->connectButton->Size = System::Drawing::Size(135, 45);
				this->connectButton->TabIndex = 1;
				this->connectButton->Text = L"Connect";
				this->connectButton->UseVisualStyleBackColor = true;
				this->connectButton->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
				// 
				// button2
				// 
				this->button2->Location = System::Drawing::Point(379, 45);
				this->button2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
				this->button2->Name = L"button2";
				this->button2->Size = System::Drawing::Size(135, 45);
				this->button2->TabIndex = 2;
				this->button2->Text = L"Refresh";
				this->button2->UseVisualStyleBackColor = true;
				this->button2->Click += gcnew System::EventHandler(this, &MyForm::refreshButton_Click);
				// 
				// comPortSelector2
				// 
				this->comPortSelector2->FormattingEnabled = true;
				this->comPortSelector2->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"Select COM Port" });
				this->comPortSelector2->Location = System::Drawing::Point(87, 103);
				this->comPortSelector2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
				this->comPortSelector2->Name = L"comPortSelector2";
				this->comPortSelector2->Size = System::Drawing::Size(266, 28);
				this->comPortSelector2->TabIndex = 4;
				this->comPortSelector2->Text = L"Select COM Port";
				this->comPortSelector2->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comPortSelector2_SelectedIndexChanged);
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Location = System::Drawing::Point(13, 45);
				this->label1->Name = L"label1";
				this->label1->Size = System::Drawing::Size(67, 20);
				this->label1->TabIndex = 5;
				this->label1->Text = L"Player A";
				// 
				// label2
				// 
				this->label2->AutoSize = true;
				this->label2->Location = System::Drawing::Point(13, 106);
				this->label2->Name = L"label2";
				this->label2->Size = System::Drawing::Size(67, 20);
				this->label2->TabIndex = 6;
				this->label2->Text = L"Player B";
				// 
				// MyForm
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(527, 214);
				this->Controls->Add(this->label2);
				this->Controls->Add(this->label1);
				this->Controls->Add(this->comPortSelector2);
				this->Controls->Add(this->button2);
				this->Controls->Add(this->connectButton);
				this->Controls->Add(this->comPortSelector);
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
				this->MaximizeBox = false;
				this->Name = L"MyForm";
				this->Text = L"Connect To Serial Device";
				this->ResumeLayout(false);
				this->PerformLayout();

			}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		try
		{
			this->serialPortToDevice->BaudRate = 9600;
			this->serialPortToDevice->Open();

			this->serialPortToDevice2->BaudRate = 9600;
			this->serialPortToDevice2->Open();
		}
		catch (UnauthorizedAccessException^ e)
		{
			MessageBox::Show("Problem Opening Serial Port", "Error");
			Application::Exit();
			this->Close();
		}
		catch (System::IO::IOException^ ie)
		{
			MessageBox::Show("Problem Opening Serial Port", "Error");
			Application::Exit();
			this->Close();
		}

		//textBox->Text = "Press 'Calibrate' to calibrate your Myo!";
		//textBox->Refresh();

		//Stupid Threading, need to leave this call here for now
		this->Hide();
	}

	private: System::Void serialPortToDevice_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {
		//std::cout << "" << std::endl;
	}

	private: System::Void serialPortToDevice_DataReceived2(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {
		//std::cout << "" << std::endl;
	}

	private: System::Void comPortSelector_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		this->serialPortToDevice->PortName = this->comPortSelector->SelectedItem->ToString();
	}

	private: System::Void comPortSelector2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		this->serialPortToDevice2->PortName = this->comPortSelector2->SelectedItem->ToString();
	}

	//public: void sendDataOverComm(unsigned char buffer[], int count) {
	public: void sendDataOverComm(int port, System::String^ dataToSend) {
		try
		{
			if (port == 1) {
				if (this->serialPortToDevice->IsOpen)
				{
					this->serialPortToDevice->WriteLine(dataToSend);
					//array<unsigned char>^ buf = { buffer[0], buffer[1], buffer[2], buffer[3], buffer[4] };
					//this->serialPortToDevice->Write(buf, 0, count);
				}
			}
			else if (port == 2) {
				if (this->serialPortToDevice2->IsOpen)
				{
					this->serialPortToDevice2->WriteLine(dataToSend);
					//array<unsigned char>^ buf = { buffer[0], buffer[1], buffer[2], buffer[3], buffer[4] };
					//this->serialPortToDevice->Write(buf, 0, count);
				}
			}

		}
		catch (int e)
		{
		}
	}
	private: System::Void refreshButton_Click(System::Object^  sender, System::EventArgs^  e) {
		this->comPortSelector->Items->Clear();
		array<String^>^ serialPorts = nullptr;
		serialPorts = this->serialPortToDevice->GetPortNames();
		for each(String^ port in serialPorts)
		{
			this->comPortSelector->Items->Add(port);
		}

		this->comPortSelector2->Items->Clear();
		serialPorts = nullptr;
		serialPorts = this->serialPortToDevice2->GetPortNames();
		for each(String^ port in serialPorts)
		{
			this->comPortSelector2->Items->Add(port);
		}
	}

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	/*	textBox->Text = "Press Connect To Start";
		textBox->Refresh();*/
	}

	private: System::Void LockingCheckBox_CheckStateChanged(System::Object^  sender, System::EventArgs^  e) {
		//this->LockingEnalbed = this->LockingCheckBox->Checked;
	}

	private: System::Void btnCalibrate_Click(System::Object^  sender, System::EventArgs^  e) {
		//calibrating = true;
		//startCalibrating = false;
		//textBox->Text = "Calibrating...";
		//textBox->Refresh();
	}

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		//textBox->Text = "Play MyoKart!";
		//textBox->Refresh();
	}

	private: System::Void textBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}


};
}
