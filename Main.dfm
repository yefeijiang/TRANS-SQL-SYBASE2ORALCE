object AutoSqlForm: TAutoSqlForm
  Left = 273
  Top = 115
  Caption = 'TRANS SQL SYBASE -> ORALCE'
  ClientHeight = 536
  ClientWidth = 971
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 971
    Height = 536
    ActivePage = TabSheet2
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #23435#20307
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object TabSheet2: TTabSheet
      Caption = 'create table sql script - SYBASE'
      ImageIndex = 1
      object Memo2: TMemo
        Left = 0
        Top = 0
        Width = 963
        Height = 201
        Align = alTop
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = #23435#20307
        Font.Style = []
        Lines.Strings = (
          
            'if  exists (select * from sysobjects where id = object_id('#39'dbo.d' +
            'isasterrecoverycfg'#39') and sysstat & 0xf = 3)'
          '    drop table dbo.disasterrecoverycfg'
          'go'
          'create table  dbo.disasterrecoverycfg ('
          
            '    enabledisasterrecovery      tinyint        default(0) not nu' +
            'll,       --'#25903#25345#22806#23616#23481#28798#21151#33021
          
            '    userexporttime              varchar(10)    not null,  --'#29992#25143#25968#25454 +
            #23450#26102#23548#20986#26102#38388'??'#36825#20010#25105#36824#35201#30830#35748#19968#19979#25968#25454#24211#37324#38656#35201#23384#25918#20160#20040#12290
          
            '    localusersavepath           varchar(250)    default('#39'/home/z' +
            'xin10/disasterbackup/local/userinfo/'#39') not null,     --'#26412#23616#29992#25143#25968#25454#22791#20221#25991 +
            #20214#20445#23384#30446#24405
          
            '    localusersavetime           int            default(3) null, ' +
            '      --'#26412#23616#29992#25143#25968#25454#22791#20221#25991#20214#20445#23384#26102#38388
          
            '    foreignusersavetime         int            default(3),      ' +
            ' --'#28798#38590#23616#29992#25143#25968#25454#22791#20221#25991#20214#20445#23384#26102#38388
          
            '    foreignsegmentsavepath      varchar(250)    default('#39'/home/z' +
            'xin10/disasterbackup/foreign/mdn/'#39') not null,     --'#28798#38590#23616#21495#27573#25968#25454#22791#20221#25991#20214#20445 +
            #23384#30446#24405
          
            '    foreignsegmentfilepath      varchar(250)    default('#39' '#39') not' +
            ' null     --'#28798#38590#23616#21495#27573#25968#25454#25991#20214#20445#23384#30446#24405
          ')'
          'go'
          
            'grant references, select, insert, delete, update on disasterreco' +
            'verycfg to dbagent'
          'go'
          
            'insert into disasterrecoverycfg(enabledisasterrecovery) values(0' +
            ')'
          'go'
          ''
          
            'if  exists (select * from sysobjects where id = object_id('#39'dbo.d' +
            'ccocs'#39') and sysstat & 0xf = 3)'
          '    drop table dbo.dccocs'
          'go'
          'create table  dbo.dccocs ('
          '    sme_index               int                    not null,'
          '    ocsnumber               varchar(50)    default('#39' '#39') not null'
          ')'
          'go'
          
            'grant references, select, insert, delete, update on dccocs to db' +
            'agent'
          'go')
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        OnClick = Memo2Click
      end
      object Panel2: TPanel
        Left = 0
        Top = 201
        Width = 963
        Height = 40
        Align = alTop
        TabOrder = 1
        object Button2: TButton
          Left = 4
          Top = 6
          Width = 75
          Height = 25
          Caption = 'Format'
          TabOrder = 0
          OnClick = Button2Click
        end
        object Button1: TButton
          Left = 85
          Top = 6
          Width = 257
          Height = 25
          Caption = 'update table sql script - SYBASE'
          Enabled = False
          TabOrder = 1
          OnClick = Button1Click
        end
        object Button3: TButton
          Left = 348
          Top = 6
          Width = 250
          Height = 25
          Caption = 'create table sql script - ORACLE'
          Enabled = False
          TabOrder = 2
          OnClick = Button3Click
        end
        object Button4: TButton
          Left = 604
          Top = 6
          Width = 245
          Height = 25
          Caption = 'update table sql script - ORACLE'
          Enabled = False
          TabOrder = 3
          OnClick = Button4Click
        end
      end
      object PageControl2: TPageControl
        Left = 0
        Top = 241
        Width = 963
        Height = 266
        ActivePage = TabSheet6
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        object TabSheet4: TTabSheet
          Caption = 'update table sql script - SYBASE'
          object Memo3: TMemo
            Left = 0
            Top = 0
            Width = 955
            Height = 237
            Align = alClient
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
            ScrollBars = ssBoth
            TabOrder = 0
            OnClick = Memo2Click
            OnKeyPress = Memo3KeyPress
          end
        end
        object TabSheet5: TTabSheet
          Caption = 'create table sql script - ORACLE'
          ImageIndex = 1
          object Memo5: TMemo
            Left = 0
            Top = 0
            Width = 955
            Height = 237
            Align = alClient
            ScrollBars = ssBoth
            TabOrder = 0
            OnClick = Memo2Click
          end
        end
        object TabSheet6: TTabSheet
          Caption = 'update table sql script - ORACLE'
          ImageIndex = 2
          object Memo6: TMemo
            Left = 0
            Top = 0
            Width = 955
            Height = 237
            Align = alClient
            ScrollBars = ssBoth
            TabOrder = 0
            OnClick = Memo2Click
          end
        end
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'ADD "GO"'
      ImageIndex = 1
      object Memo1: TMemo
        Left = 3
        Top = 3
        Width = 957
        Height = 454
        TabOrder = 0
      end
      object LabeledEdit1: TLabeledEdit
        Left = 24
        Top = 484
        Width = 169
        Height = 21
        EditLabel.Width = 98
        EditLabel.Height = 13
        EditLabel.Caption = 'EVERY 100 ROWS'
        TabOrder = 1
        Text = 'GO'
      end
      object Button5: TButton
        Left = 440
        Top = 473
        Width = 75
        Height = 25
        Caption = 'GO'
        TabOrder = 2
        OnClick = Button5Click
      end
    end
  end
end
