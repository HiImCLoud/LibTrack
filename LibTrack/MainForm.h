#ifndef MainFormH
#define MainFormH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Imaging.jpeg.hpp>

class TForm2 : public TForm
{
__published:
    TImage  *ImageBackground;
    TEdit   *EditBookName;
    TListBox*ListBooks;
    TButton *BtnAdd;
    TButton *BtnBorrow;
    TButton *BtnReturn;
    TLabel  *LblStatus;

    void __fastcall FormShow      (TObject *Sender);
    void __fastcall ListBooksClick(TObject *Sender);
    void __fastcall BtnAddClick   (TObject *Sender);
    void __fastcall BtnBorrowClick(TObject *Sender);
    void __fastcall BtnReturnClick(TObject *Sender);

public:
    void LoadBooks ();
	void SaveBooks ();
    void UpdateStatus(const String& msg, TColor color);

public:
    __fastcall TForm2(TComponent* Owner);
};

extern PACKAGE TForm2 *Form2;
#endif

