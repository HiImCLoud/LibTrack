//---------------------------------------------------------------------------

#ifndef LoginFormH
#define LoginFormH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "MainForm.h"

//---------------------------------------------------------------------------

class TForm1 : public TForm
{
__published:
    TImage *ImageBackground;
    TEdit *EditUsername;
    TEdit *EditPassword;
    TButton *BtnLogin;
    TLabel *LblStatus;

    void __fastcall BtnLoginClick(TObject *Sender);

private:
public:
    __fastcall TForm1(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

