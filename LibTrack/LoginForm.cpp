//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <System.IOUtils.hpp>
#include "LoginForm.h"
#include "MainForm.h"
#include <fstream>
#include <string>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
	this->Caption = "Library Tracker - Login Form";
	EditPassword->PasswordChar = '*';
	EditUsername->TextHint = "Enter your username";
    EditPassword->TextHint = "Enter your password";
}

//---------------------------------------------------------------------------

void __fastcall TForm1::BtnLoginClick(TObject *Sender)
{
    String inputUser = EditUsername->Text.Trim();
    String inputPass = EditPassword->Text.Trim();

    if (inputUser.IsEmpty() || inputPass.IsEmpty()) {
        LblStatus->Caption = "Please enter username and password.";
        LblStatus->Font->Color = clRed;
        LblStatus->Visible = true;
        return;
    }

    String fullPath = TPath::Combine(ExtractFilePath(Application->ExeName), "users.txt");

    std::ifstream file(fullPath.c_str());
    if (!file.is_open()) {
        LblStatus->Caption = "Unable to open users.txt.";
        LblStatus->Font->Color = clRed;
        LblStatus->Visible = true;
        return;
    }

    bool loginSuccess = false;
    std::string line;
    while (std::getline(file, line)) {
        int commaPos = line.find(',');
        if (commaPos == std::string::npos) continue;

        std::string user = line.substr(0, commaPos);
        std::string pass = line.substr(commaPos + 1);

        if (inputUser == user.c_str() && inputPass == pass.c_str()) {
            loginSuccess = true;
            break;
        }
    }
    file.close();

	if (loginSuccess) {
		LblStatus->Caption = "Login successful!";
		LblStatus->Font->Color = clGreen;
		LblStatus->Visible = true;

		Form1->Hide();

		if (!Form2)
			Application->CreateForm(__classid(TForm2), &Form2);

		Form2->LoadBooks();
		Form2->Show();
	}

    else {
        LblStatus->Caption = "Invalid username or password!";
        LblStatus->Font->Color = clRed;
        LblStatus->Visible = true;
    }
}

