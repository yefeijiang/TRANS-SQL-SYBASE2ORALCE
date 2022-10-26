// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include <StrUtils.hpp>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAutoSqlForm *AutoSqlForm;

// ---------------------------------------------------------------------------
__fastcall TAutoSqlForm::TAutoSqlForm(TComponent* Owner) : TForm(Owner) {

}
// ---------------------------------------------------------------------------

void TAutoSqlForm::Sql2SybaseUpdateSql() {
	TStringList *psql = new TStringList;
	psql->Text = Memo2->Text;
	int endindex = 0;
	for (int i = 0; i < psql->Count; i++) {
		if ((psql->Strings[i].Pos("EXISTS") != 0) &&
			(psql->Strings[i].Pos("NOT EXISTS") == 0)) {
			psql->Strings[i] = AnsiReplaceText(psql->Strings[i], "EXISTS",
				"NOT EXISTS");
		}

		if (psql->Strings[i].Pos("DROP TABLE") != 0) {
			psql->Strings[i] = "    BEGIN";
		}
		if (psql->Strings[i].Pos("CREATE TABLE") != 0) {
			psql->Strings[i] = "        EXEC('" + Trim(psql->Strings[i]);
			i++;
			bool arriveGo = false;
			while (!arriveGo) {
				psql->Strings[i] = "                                   " +
				AnsiReplaceText(Trim(psql->Strings[i]).c_str(), "'", "''");
				if (Trim(psql->Strings[i]) == ")") {
					psql->Strings[i] = psql->Strings[i] + "')";
				}

				if (i < psql->Count-1) {
					i++;
				}
				else {
					break;
				}
				arriveGo = (psql->Strings[i].Pos("GO") != 0);
			}
			psql->Strings[i] = "    END";
			endindex = i;
		}
		if ((psql->Strings[i].Pos("GRANT") != 0) && (psql->Strings[i].Pos
				("EXEC('GRANT") == 0)) {
			psql->Strings[i] = "        EXEC('" + AnsiReplaceText
			(Trim(psql->Strings[i]).c_str(), "'", "''") + "')";
			psql->Insert(endindex, psql->Strings[i]);
			psql->Delete(i + 1);
			endindex++;
		}
		if ((psql->Strings[i].Pos("INSERT") != 0) && (psql->Strings[i].Pos
				("EXEC('INSERT") == 0)) {
			psql->Strings[i] = "        EXEC('" + AnsiReplaceText
			(Trim(psql->Strings[i]).c_str(), "'", "''") + "')";
			psql->Insert(endindex, psql->Strings[i]);
			psql->Delete(i + 1);
			endindex++;
		}
	}

	for (int i = 0; i < psql->Count; i++) {
		/*
		if((psql->Strings[i].Pos("GRANT")!=0)&&(psql->Strings[i].Pos("EXEC('GRANT")==0))
		{
		psql->Strings[i] = "        EXEC('"+AnsiReplaceText(Trim(psql->Strings[i]).c_str(),"'","''")+"')";
		//psql->Insert(endindex,psql->Strings[i]);
		//psql->Delete(i+1);
		//endindex++;
		} */
		if (psql->Strings[i].Pos("GO") != 0) {
			psql->Delete(i);
		}
	}
	psql->Add("GO");
	Memo3->Text = psql->Text;
	delete psql;
}

// ---------------------------------------------------------------------------
AnsiString TAutoSqlForm::FormatKeyWords(AnsiString keywordsstring) {
	TStringList *pKeyWordList;
	pKeyWordList = new TStringList;
	pKeyWordList->LoadFromFile("keyword.list");
	for (int i = 0; i < pKeyWordList->Count; i++) {
		keywordsstring = AnsiReplaceText(keywordsstring, '\t', "    ");
		keywordsstring = AnsiReplaceText
		(keywordsstring, pKeyWordList->Strings[i].c_str(), pKeyWordList->Strings[i].c_str());
	}
	delete pKeyWordList;
	return keywordsstring;
}

// ---------------------------------------------------------------------------
void TAutoSqlForm::Sql2OracleCreateSql() {
	TStringList *psql = new TStringList;
	TStringList *pkeyword = new TStringList;
	pkeyword->LoadFromFile("sybase2oracle.list");
	psql->Text = Memo2->Text;
	for (int i = 0; i < psql->Count; i++) {
		if (psql->Strings[i].Pos("EXISTS") != 0) {
			psql->Delete(i);
			i--;
			continue;
		}
		if (psql->Strings[i].Pos("DROP TABLE") != 0) {
			psql->Strings[i] = AnsiReplaceText
			(psql->Strings[i], "DROP TABLE", "");
			psql->Strings[i] = AnsiReplaceText(psql->Strings[i], "dbo.", "");
			psql->Strings[i] = AnsiReplaceText(psql->Strings[i], ")", "");
			psql->Strings[i] = "    droptable('" + Trim(psql->Strings[i])
			+ "');";
			psql->Insert(i, "BEGIN");
			psql->Insert(i + 2, "END;");
			i++;
			continue;
		}
		if (psql->Strings[i].Pos("GRANT") != 0) {
			psql->Delete(i);
			i--;
			if (psql->Strings[i].Pos("GO") != 0) {
				psql->Delete(i);
				i--;
			}
		}
	}
	TStringList *needreplace = new TStringList;
	needreplace->Delimiter = '|';
	for (int i = 0; i < pkeyword->Count; i++) {
		needreplace->DelimitedText = pkeyword->Strings[i];
		psql->Text = AnsiReplaceText(psql->Text, needreplace->Strings[0],
			needreplace->Strings[1]);
	}
	Memo5->Text = psql->Text;
	delete psql;
	delete pkeyword;
	delete needreplace;
}

void TAutoSqlForm::Sql2OracleUpdateSql() {
	TStringList *psql = new TStringList;
	psql->Text = Memo5->Text;
	int endindex = 0;
	for (int i = 0; i < psql->Count; i++) {
		if ((psql->Strings[i].Pos("CREATE TABLE") == 0) &&
			(psql->Strings[i].Pos("INSERT") == 0)) {
			psql->Delete(i);
			i--;
			continue;
		}
		if (psql->Strings[i].Pos("CREATE TABLE") != 0) {
			psql->Insert(i, "DECLARE");
			i++;
			psql->Insert(i, "    tablecount number;");
			i++;
			psql->Insert(i, "BEGIN");
			i++;
			psql->Insert(i, "    tablecount:= 0;");
			i++;
			psql->Insert(i,
				"    SELECT COUNT(*) INTO tablecount FROM user_tables where table_name='$TABLENAME';");
			i++;
			psql->Insert(i, "    IF  (tablecount <1) THEN");
			i++;
			AnsiString tablename = psql->Strings[i];
			tablename = AnsiReplaceText(tablename, "CREATE TABLE", "");
			tablename = AnsiReplaceText(tablename, "(", "");
			tablename = Trim(tablename);
			psql->Text = AnsiReplaceText(psql->Text, "$TABLENAME", UpperCase
				(tablename));
			psql->Strings[i] = "        EXECUTE IMMEDIATE '" + Trim
			(psql->Strings[i]);
			i++;
			bool arriveGo = false;
			while (!arriveGo) {
				psql->Strings[i] = "                                   " +
				AnsiReplaceText(Trim(psql->Strings[i]).c_str(), "'", "''");
				if (Trim(psql->Strings[i]) == ")") {
					psql->Strings[i] = psql->Strings[i] + "';";
				}
				i++;
				arriveGo = (Trim(psql->Strings[i]).Pos("/") == 1);
			}
			endindex = i;
			psql->Strings[i] = "    END IF;";
			psql->Insert(i + 1, "END;");
			i++;
			psql->Insert(i + 1, "/");
			i++;
			psql->Insert(i + 1, "");
			i++;
		}
		if (psql->Strings[i].Pos("INSERT") != 0) {
			psql->Strings[i] = "        EXECUTE IMMEDIATE '" + AnsiReplaceText
			(Trim(psql->Strings[i]).c_str(), "'", "''") + "';";
			psql->Insert(endindex, psql->Strings[i]);
			psql->Delete(i + 1);
			endindex++;
		}
	}
	Memo6->Text = psql->Text;
	delete psql;
}

AnsiString TAutoSqlForm::SqlFormat(AnsiString sqlmemo) {
	TStringList *pmemo = new TStringList;
	AnsiString sql = "";
	TStringList *plist = new TStringList;

	plist->Delimiter = ' ';
	sqlmemo = AnsiReplaceText(sqlmemo, "not null", "NOT*NULL");
	sqlmemo = AnsiReplaceText(sqlmemo, "default(' ')", "DEFAULT('*')");
	pmemo->Text = sqlmemo;

	AnsiString explain = "";
	int pos = 0;

	for (int m = 0; m < pmemo->Count; m++) {

		sql = pmemo->Strings[m];
		//
		pos = sql.Pos("--");
		if (pos != 0) {
			explain = sql.SubString(pos, sql.Length());
		}
		sql = sql.Delete(pos, sql.Length());
		if (sql.Pos(",") == 0) {
			AnsiString temp1 = "";
			AnsiString temp2 = "";
			temp1 = Trim(sql);
			if (temp1.IsEmpty())
				continue;
			temp1 = temp1.SubString(temp1.Length(), 1);
			if ((m - 1) < 0)
				continue;
			temp2 = pmemo->Strings[m - 1];
			temp2 = Trim(temp2);
			if (temp2.IsEmpty())
				continue;
			temp2 = temp2.SubString(temp2.Length(), 1);
			if ((temp1.IsEmpty()) || (temp2.IsEmpty()))
				continue;
			if ((temp1 != ",") && (temp2 == ","))
				continue;
		}

		plist->DelimitedText = sql;
		if (plist->Count < 3) {
			plist->Insert(2, "");
			plist->Insert(3, "");
		}
		else {
			if (plist->Count < 4) {
				if (plist->Strings[2].Pos("DEFAULT") == 0) {
					plist->Insert(2, "");
				}
				else {
					plist->Insert(3, "");
				}
			}
		}
		plist->Strings[0] = "    " + fillstring(Trim(plist->Strings[0]), 30);
		plist->Strings[1] = fillstring(Trim(plist->Strings[1]), 20);
		plist->Strings[2] = fillstring(Trim(plist->Strings[2]), 20);
		plist->Strings[3] = fillstring(Trim(plist->Strings[3]), 20);
		sql = "";

		for (int i = 0; i < plist->Count; i++) {
			sql += plist->Strings[i];
		}

		sql = AnsiReplaceText(sql, "*", " ");
		pmemo->Strings[m] = sql;
	}
	sql = pmemo->Text;
	delete plist;
	delete pmemo;
	return sql;

}

AnsiString TAutoSqlForm::fillstring(AnsiString sql, int length) {
	int filllength = abs(length - sql.Length());
	for (int i = 0; i < filllength; i++) {
		sql += " ";
	}
	return sql;

}

void __fastcall TAutoSqlForm::Memo3KeyPress(TObject *Sender, char &Key) {
	if ((Key == 'a') && (Key == VK_CONTROL)) {
		Memo3->SelectAll();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TAutoSqlForm::Memo2Click(TObject *Sender) {
	TMemo *memo;
	memo = dynamic_cast<TMemo*>(Sender);
	memo->SelectAll();
}
// ---------------------------------------------------------------------------

void __fastcall TAutoSqlForm::Button2Click(TObject *Sender) {
	Memo2->Text = FormatKeyWords(Memo2->Text);
	// Memo2->Text = SqlFormat(Memo2->Text);
	Button1->Enabled = true;
	Button3->Enabled = true;
	Button4->Enabled = true;
}

// ---------------------------------------------------------------------------
void __fastcall TAutoSqlForm::Button1Click(TObject *Sender) {
	Sql2SybaseUpdateSql();
	PageControl2->ActivePageIndex = 0;
}
// ---------------------------------------------------------------------------

void __fastcall TAutoSqlForm::Button3Click(TObject *Sender) {
	Sql2OracleCreateSql();
	PageControl2->ActivePageIndex = 1;
}
// ---------------------------------------------------------------------------

void __fastcall TAutoSqlForm::Button4Click(TObject *Sender) {
	Sql2OracleUpdateSql();
	PageControl2->ActivePageIndex = 2;
}
// ---------------------------------------------------------------------------

void __fastcall TAutoSqlForm::Button5Click(TObject *Sender) {
	TStringList *psql = new TStringList;
	psql->Text = Memo1->Text;
	for (int i = 0; i < psql->Count; i += 100) {
		psql->Insert(i, "GO");
	}
	Memo1->Text = psql->Text;
	delete psql;
}
// ---------------------------------------------------------------------------
