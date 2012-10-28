object Form1: TForm1
  Left = 349
  Top = 112
  BorderStyle = bsSingle
  Caption = 'Choose item parameters...'
  ClientHeight = 300
  ClientWidth = 310
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 8
    Width = 92
    Height = 13
    Caption = 'Application address'
  end
  object Label2: TLabel
    Left = 24
    Top = 64
    Width = 262
    Height = 13
    Caption = 'Additional info (usually, file to open with that application)'
  end
  object Label3: TLabel
    Left = 24
    Top = 112
    Width = 159
    Height = 13
    Caption = 'Working directory (not neccesary)'
  end
  object Label4: TLabel
    Left = 24
    Top = 160
    Width = 59
    Height = 13
    Caption = 'Launch type'
  end
  object Label5: TLabel
    Left = 24
    Top = 208
    Width = 30
    Height = 13
    Caption = 'Action'
  end
  object Edit1: TEdit
    Left = 24
    Top = 32
    Width = 185
    Height = 21
    TabOrder = 0
  end
  object Edit2: TEdit
    Left = 24
    Top = 80
    Width = 185
    Height = 21
    TabOrder = 1
  end
  object Edit3: TEdit
    Left = 24
    Top = 128
    Width = 185
    Height = 21
    TabOrder = 2
  end
  object Button1: TButton
    Left = 224
    Top = 32
    Width = 75
    Height = 25
    Caption = 'Browse...'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 224
    Top = 80
    Width = 75
    Height = 25
    Caption = 'Browse...'
    TabOrder = 4
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 224
    Top = 128
    Width = 75
    Height = 25
    Caption = 'Browse...'
    TabOrder = 5
    OnClick = Button3Click
  end
  object ComboBox1: TComboBox
    Left = 24
    Top = 176
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 6
    Text = 'SW_SHOW'
    Items.Strings = (
      'SW_SHOW'
      'SW_HIDE'
      'SW_MAXIMIZE'
      'SW_MINIMIZE'
      'SW_RESTORE'
      'SW_SHOWDEFAULT'
      'SW_SHOWMAXIMIZED'
      'SW_SHOWMINIMIZED'
      'SW_SHOWMINNOACTIVE'
      'SW_SHOWNA'
      'SW_SHOWNOACTIVATE'
      'SW_SHOWNORMAL')
  end
  object ComboBox2: TComboBox
    Left = 24
    Top = 224
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 7
    Text = 'open'
    Items.Strings = (
      'open'
      'edit'
      'explore'
      'find'
      'print'
      'NULL')
  end
  object Button4: TButton
    Left = 136
    Top = 264
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 8
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 224
    Top = 264
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 9
    OnClick = Button5Click
  end
  object OpenDialog1: TOpenDialog
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 65528
    Top = 24
  end
  object OpenDialog2: TOpenDialog
    Left = 65528
    Top = 80
  end
  object OpenDialog3: TOpenDialog
    Left = 65528
    Top = 120
  end
end
