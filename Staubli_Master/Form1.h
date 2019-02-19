#include "Staubli_Master.h"
#pragma once

namespace Staubli_Master {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			dtx_data_location = gcnew array<System::String ^> {"x=", "y=", "z=", "rx=", "ry=", "rz="};
			connect_OK = false;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private : System::Boolean ^file_selected;
	private : System::String ^file_path;
	private : System::String ^dtx_data;
	private : array<System::String ^> ^dtx_data_location;
	private : bool connect_OK;

	private: System::Windows::Forms::Button^  B_connect;
	private: System::Windows::Forms::TextBox^  T_filepath;

	private: System::Windows::Forms::Button^  B_openfile_dialog;
	private: System::Windows::Forms::Button^  B_transfer;


	private: System::Windows::Forms::OpenFileDialog^  openfile_dialog;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  T_robotip;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  T_log;






	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->B_connect = (gcnew System::Windows::Forms::Button());
			this->T_filepath = (gcnew System::Windows::Forms::TextBox());
			this->B_openfile_dialog = (gcnew System::Windows::Forms::Button());
			this->B_transfer = (gcnew System::Windows::Forms::Button());
			this->openfile_dialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->T_robotip = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->T_log = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// B_connect
			// 
			this->B_connect->Location = System::Drawing::Point(108, 74);
			this->B_connect->Name = L"B_connect";
			this->B_connect->Size = System::Drawing::Size(67, 23);
			this->B_connect->TabIndex = 0;
			this->B_connect->Text = L"Connect";
			this->B_connect->UseVisualStyleBackColor = true;
			this->B_connect->Click += gcnew System::EventHandler(this, &Form1::B_connect_Click);
			// 
			// T_filepath
			// 
			this->T_filepath->Location = System::Drawing::Point(12, 23);
			this->T_filepath->Name = L"T_filepath";
			this->T_filepath->Size = System::Drawing::Size(204, 20);
			this->T_filepath->TabIndex = 1;
			this->T_filepath->TextChanged += gcnew System::EventHandler(this, &Form1::T_filepath_TextChanged);
			// 
			// B_openfile_dialog
			// 
			this->B_openfile_dialog->Location = System::Drawing::Point(222, 23);
			this->B_openfile_dialog->Name = L"B_openfile_dialog";
			this->B_openfile_dialog->Size = System::Drawing::Size(50, 24);
			this->B_openfile_dialog->TabIndex = 2;
			this->B_openfile_dialog->Text = L". . . . . . .";
			this->B_openfile_dialog->UseVisualStyleBackColor = true;
			this->B_openfile_dialog->Click += gcnew System::EventHandler(this, &Form1::B_openfile_dialog_Click);
			// 
			// B_transfer
			// 
			this->B_transfer->Location = System::Drawing::Point(181, 53);
			this->B_transfer->Name = L"B_transfer";
			this->B_transfer->Size = System::Drawing::Size(91, 43);
			this->B_transfer->TabIndex = 3;
			this->B_transfer->Text = L"Transfer";
			this->B_transfer->UseVisualStyleBackColor = true;
			this->B_transfer->Click += gcnew System::EventHandler(this, &Form1::B_transfer_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(10, 56);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(90, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Robot IP Address";
			// 
			// T_robotip
			// 
			this->T_robotip->Location = System::Drawing::Point(12, 73);
			this->T_robotip->Name = L"T_robotip";
			this->T_robotip->Size = System::Drawing::Size(90, 20);
			this->T_robotip->TabIndex = 5;
			this->T_robotip->TextChanged += gcnew System::EventHandler(this, &Form1::T_robotip_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(10, 7);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(81, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"File To Transfer";
			// 
			// T_log
			// 
			this->T_log->Location = System::Drawing::Point(12, 119);
			this->T_log->Multiline = true;
			this->T_log->Name = L"T_log";
			this->T_log->ReadOnly = true;
			this->T_log->Size = System::Drawing::Size(260, 130);
			this->T_log->TabIndex = 7;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->T_log);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->T_robotip);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->B_transfer);
			this->Controls->Add(this->B_openfile_dialog);
			this->Controls->Add(this->T_filepath);
			this->Controls->Add(this->B_connect);
			this->Name = L"Form1";
			this->Text = L"Lanco Polishing";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public:
		System::String ^ip;

	private: System::Void B_connect_Click(System::Object^  sender, System::EventArgs^  e) {
				 //if ( !(ip->Empty) && (ip->Length == 14) ) {
				 T_robotip->ReadOnly = true;
					 T_robotip->Text = "169.254.95.22";
					 if (server.PingEcho("169.254.95.22")) {
						 T_log->Text = T_log->Text+L"server reachable"+System::Environment::NewLine;
						 server.PingReply_Listen();

						 connect_OK = true;
					 }
					 else {
						 system("cls");
						 T_log->Text = T_log->Text+L"Unreachable server"+System::Environment::NewLine;

						 connect_OK  = false;
					 }
				 //}
			 }
	private: System::Void T_robotip_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 ip = T_robotip->Text;
			 }
	private: System::Void B_openfile_dialog_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (openfile_dialog->ShowDialog()== System::Windows::Forms::DialogResult::OK)
				 {
					 T_filepath->Text = openfile_dialog->FileName;
				 }
			 }
	private: System::Void B_transfer_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (file_selected && connect_OK) {
					 _beginthread((void (*)(void *))TranHandle, 0, (void *)FileHandle::SysString_StdString(file_path));
					 T_log->Text = T_log->Text+L"Data Sending......"+System::Environment::NewLine;
				 } else
					 T_log->Text = T_log->Text+L"Robot Not Connected"+System::Environment::NewLine;
				 B_connect->Text = "Connect";
			 }
	private: System::Void T_filepath_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (T_filepath->Text != ""){
					 file_path = T_filepath->Text;
					 T_log->Text = T_log->Text+L"File Selected"+System::Environment::NewLine;

					 file_selected = true;
				 } else
					 file_selected = false;
			 }
};
}

