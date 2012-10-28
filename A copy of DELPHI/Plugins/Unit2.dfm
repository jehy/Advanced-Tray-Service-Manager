object Form2: TForm2
  Left = 399
  Top = 94
  BorderStyle = bsSingle
  Caption = 'Choose file or directory'
  ClientHeight = 309
  ClientWidth = 514
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
  object DriveComboBox1: TDriveComboBox
    Left = 8
    Top = 16
    Width = 113
    Height = 19
    DirList = DirectoryListBox1
    TabOrder = 0
  end
  object DirectoryListBox1: TDirectoryListBox
    Left = 8
    Top = 48
    Width = 217
    Height = 217
    FileList = FileListBox1
    ItemHeight = 16
    TabOrder = 1
  end
  object FileListBox1: TFileListBox
    Left = 240
    Top = 48
    Width = 257
    Height = 217
    ItemHeight = 13
    TabOrder = 2
    OnDblClick = FileListBox1DblClick
  end
  object Button1: TButton
    Left = 240
    Top = 272
    Width = 129
    Height = 25
    Caption = 'Choose selected directory'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 384
    Top = 272
    Width = 113
    Height = 25
    Caption = 'Choose selected file'
    TabOrder = 4
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 144
    Top = 272
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 5
    OnClick = Button3Click
  end
  object FilterComboBox1: TFilterComboBox
    Left = 312
    Top = 16
    Width = 185
    Height = 21
    FileList = FileListBox1
    Filter = 'All files (*.*)|*.*|Executable|*.exe'
    TabOrder = 6
  end
end
