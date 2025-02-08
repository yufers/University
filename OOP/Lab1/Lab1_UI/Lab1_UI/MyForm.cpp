#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

public ref class MyForm : public System::Windows::Forms::Form
{
public:
    MyForm()
    {
		System::Windows::Forms::ComboBox^ comboBox = gcnew System::Windows::Forms::ComboBox();
		comboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

		array<String^>^ items = { "Общие элементы", "Документы", "Изображения", "Музыка", "Видео" };
		comboBox->Items->AddRange(items);
		comboBox->SelectedIndex = 0;

		comboBox->Location = System::Drawing::Point(10, 45);
		comboBox->Size = System::Drawing::Size(304, 21);

		this->Controls->Add(comboBox);
    }
};

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Lab1Forms::MyForm form;
	Application::Run(% form);
}