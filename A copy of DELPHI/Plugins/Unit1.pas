unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, unit2;
type
  TForm1 = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    OpenDialog1: TOpenDialog;
    OpenDialog2: TOpenDialog;
    OpenDialog3: TOpenDialog;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    ComboBox1: TComboBox;
    ComboBox2: TComboBox;
    Label4: TLabel;
    Label5: TLabel;
    Button4: TButton;
    Button5: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations } 
   res: Pchar;
  end;

//var
  //Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var FileDlg: TForm2;
begin
FileDlg:=Tform2.Create(Application);
FileDlg.ShowModal();
if(FileDlg.ChosenFile<>nil)
  then Edit1.Text:=FileDlg.ChosenFile;
FileDlg.Free;
StrDispose(FileDlg.ChosenFile);
end;

procedure TForm1.Button2Click(Sender: TObject);
var FileDlg: TForm2;
begin
FileDlg:=Tform2.Create(Application);
FileDlg.ShowModal();
if(FileDlg.ChosenFile<>nil)
  then Edit2.Text:=FileDlg.ChosenFile;
FileDlg.Free;
StrDispose(FileDlg.ChosenFile);
end;

procedure TForm1.Button3Click(Sender: TObject);
var FileDlg: TForm2;
begin
FileDlg:=Tform2.Create(Application);
FileDlg.ShowModal();
if(FileDlg.ChosenFile<>nil)
  then Edit3.Text:=FileDlg.ChosenFile;
FileDlg.Free;
StrDispose(FileDlg.ChosenFile);
end;

procedure TForm1.Button5Click(Sender: TObject);
var
contents: string;
temp: pchar;
begin
contents:='<app>'+Edit1.text+'</app><way>'+Edit2.Text+'</way><dir>'+Edit3.Text+
'</dir><launch>'+ComboBox1.Text+'</launch><action>'+ComboBox2.Text+'</action>';
temp:=pchar(contents);
res:=StrAlloc(strlen(temp)+1);
StrCopy(res,temp);
Close();
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
//res:=StrAlloc(7);
//StrCopy(res,'fuck2');
res:=nil;
Close();
end;


end.
