unit Unit2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, FileCtrl, StdCtrls;

type
  TForm2 = class(TForm)
    DriveComboBox1: TDriveComboBox;
    DirectoryListBox1: TDirectoryListBox;
    FileListBox1: TFileListBox;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    FilterComboBox1: TFilterComboBox;
    procedure Button1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    //procedure DirectoryListBox1DblClick(Sender: TObject);
    procedure FileListBox1DblClick(Sender: TObject);

  private
    { Private declarations }
  public
    ChosenFile: PChar;
    { Public declarations }
  end;

var
  Form2: TForm2;

implementation

{$R *.dfm}

procedure TForm2.Button1Click(Sender: TObject);
var
  contents: string;
  temp: pchar;
begin
//contents:=DriveComboBox1.Drive;
contents:=DirectoryListBox1.Directory;
temp:=pchar(contents);
ChosenFile:=StrAlloc(strlen(temp)+1);
StrCopy(ChosenFile,temp);
Close();
end;

procedure TForm2.Button3Click(Sender: TObject);
begin
ChosenFile:=nil;
Close();
end;

procedure TForm2.Button2Click(Sender: TObject);
var
  contents: string;
  temp: pchar;
begin
//contents:=DriveComboBox1.Drive;
//contents:=contents+DirectoryListBox1.Directory;
contents:=FileListBox1.FileName;
temp:=pchar(contents);
ChosenFile:=StrAlloc(strlen(temp)+1);
StrCopy(ChosenFile,temp);
Close();
end;
    {
procedure TForm2.DirectoryListBox1DblClick(Sender: TObject);
begin
Button1Click(self);
end; }

procedure TForm2.FileListBox1DblClick(Sender: TObject);
begin
Button2Click(self);
end;

end.
