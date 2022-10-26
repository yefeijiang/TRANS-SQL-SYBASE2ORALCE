//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#define MAX(a,b)   (a>b?a:b)
class TAutoSqlForm : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl1;
    TTabSheet *TabSheet2;
    TMemo *Memo2;
    TPanel *Panel2;
    TButton *Button2;
    TPageControl *PageControl2;
    TTabSheet *TabSheet4;
    TTabSheet *TabSheet5;
    TTabSheet *TabSheet6;
    TMemo *Memo3;
    TMemo *Memo5;
    TMemo *Memo6;
	TButton *Button1;
	TButton *Button3;
	TButton *Button4;
	TTabSheet *TabSheet1;
	TMemo *Memo1;
	TLabeledEdit *LabeledEdit1;
	TButton *Button5;
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Memo3KeyPress(TObject *Sender, char &Key);
	void __fastcall Memo2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TAutoSqlForm(TComponent* Owner);
	AnsiString FormatKeyWords(AnsiString keywordsstring);

	AnsiString SqlFormat(AnsiString sqlmemo);
	AnsiString fillstring(AnsiString sql,int length);
    void Sql2SybaseUpdateSql();
    void Sql2OracleCreateSql();
    void Sql2OracleUpdateSql();
    
};
//---------------------------------------------------------------------------
extern PACKAGE TAutoSqlForm *AutoSqlForm;
//---------------------------------------------------------------------------
#endif
