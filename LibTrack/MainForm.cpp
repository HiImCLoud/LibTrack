#include <vcl.h>
#pragma hdrstop
#include "MainForm.h"
#include <fstream>
#include <System.IOUtils.hpp>

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm2 *Form2;

// ───────────────────────────────────────────────────────────────
//  ctor
// ───────────────────────────────────────────────────────────────
__fastcall TForm2::TForm2(TComponent* Owner): TForm(Owner)
{
    Caption             = "Library Tracker – Main Menu";
    ListBooks->Font->Name = "Courier New";
    ListBooks->Font->Size = 10;
    ListBooks->OnClick    = ListBooksClick;   // bind click
}

// ───────────────────────────────────────────────────────────────
//  Restore list each time form is shown
// ───────────────────────────────────────────────────────────────
void __fastcall TForm2::FormShow(TObject *) { LoadBooks(); }

// ───────────────────────────────────────────────────────────────
//  Add book
// ───────────────────────────────────────────────────────────────
void __fastcall TForm2::BtnAddClick(TObject *)
{
    String book = EditBookName->Text.Trim();
    if (book.IsEmpty())          { UpdateStatus("Enter a book title.", clRed); return; }

    // ensure header present
    if (ListBooks->Items->Count == 0 ||
        ListBooks->Items->Strings[0].Pos("Book Title") != 1)
        ListBooks->Items->Insert(0, Format("%-40s\t%s", ARRAYOFCONST(("Book Title", "Status"))));

    // duplicate?
    for (int i=1;i<ListBooks->Items->Count;++i){
        int p = ListBooks->Items->Strings[i].LastDelimiter("\t");
        if (p>0 && ListBooks->Items->Strings[i].SubString(1,p-1).Trim().LowerCase()==book.LowerCase()){
            UpdateStatus("Book already exists.",clRed); return;
        }
    }

    ListBooks->Items->Add(Format("%-40s\t%s", ARRAYOFCONST((book,"Available"))));
    EditBookName->Clear();
    SaveBooks();
    UpdateStatus("Book added.",clGreen);
}

// ───────────────────────────────────────────────────────────────
void __fastcall TForm2::BtnBorrowClick(TObject *)
{
    int idx = ListBooks->ItemIndex; if (idx<=0){UpdateStatus("Select a book.",clRed);return;}

    String row = ListBooks->Items->Strings[idx];
    int tab   = row.LastDelimiter("\t");     if (tab==0) {UpdateStatus("Bad row.",clRed);return;}

    String name   = row.SubString(1, tab-1).Trim();
    String status = row.SubString(tab+1, row.Length()-tab).Trim();
    if (status=="Borrowed"){UpdateStatus("Already borrowed.",clRed);return;}

    ListBooks->Items->Strings[idx]=Format("%-40s\t%s", ARRAYOFCONST((name,"Borrowed")));
    SaveBooks();
    UpdateStatus("Borrowed.",clGreen);
}

// ───────────────────────────────────────────────────────────────
void __fastcall TForm2::BtnReturnClick(TObject *)
{
    int idx = ListBooks->ItemIndex; if (idx<=0){UpdateStatus("Select a book.",clRed);return;}

    String row = ListBooks->Items->Strings[idx];
    int tab   = row.LastDelimiter("\t");     if (tab==0){UpdateStatus("Bad row.",clRed);return;}

    String name   = row.SubString(1, tab-1).Trim();
    String status = row.SubString(tab+1, row.Length()-tab).Trim();
    if (status=="Available"){UpdateStatus("Already available.",clRed);return;}

    ListBooks->Items->Strings[idx]=Format("%-40s\t%s", ARRAYOFCONST((name,"Available")));
    SaveBooks();
    UpdateStatus("Returned.",clGreen);
}

// ───────────────────────────────────────────────────────────────
//  SAVE  – rewrite file with all current rows (skips header)
// ───────────────────────────────────────────────────────────────
void TForm2::SaveBooks()
{
    if (ListBooks->Items->Count<=1) return;

    String path = TPath::Combine(ExtractFilePath(Application->ExeName),"books.txt");
    std::ofstream out(path.c_str(), std::ios::out|std::ios::trunc);

    for (int i=1;i<ListBooks->Items->Count;++i){
        out << AnsiString(ListBooks->Items->Strings[i]).c_str() << '\n';
    }
    out.close();
}

// ───────────────────────────────────────────────────────────────
//  LOAD  – read file and populate list (adds header)
// ───────────────────────────────────────────────────────────────
void TForm2::LoadBooks()
{
    String header = Format("%-40s\t%s", ARRAYOFCONST(("Book Title","Status")));
    ListBooks->Items->Clear();
    ListBooks->Items->Add(header);

    String path = TPath::Combine(ExtractFilePath(Application->ExeName),"books.txt");
    if (!FileExists(path)) return;

    std::ifstream in(path.c_str());
    std::string line;
    while (std::getline(in,line)){
        String s = String(line.c_str()).Trim();
        if (!s.IsEmpty()) ListBooks->Items->Add(s);
    }
    in.close();
}

// ───────────────────────────────────────────────────────────────
void TForm2::UpdateStatus(const String& msg, TColor col)
{
    LblStatus->Caption = msg;
    LblStatus->Font->Color = col;
    LblStatus->Visible = true;
}

// ───────────────────────────────────────────────────────────────
void __fastcall TForm2::ListBooksClick(TObject *)
{
    int idx = ListBooks->ItemIndex;
    if (idx<=0){EditBookName->Text="";return;}

    String row = ListBooks->Items->Strings[idx];
    int tab    = row.LastDelimiter("\t");
    EditBookName->Text = (tab>0) ? row.SubString(1,tab-1).Trim() : row;
}

