unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, Grids;//, unit2;
type
  TForm1 = class(TForm)
    Button4: TButton;
    Button5: TButton;
    CheckBox1: TCheckBox;
    RadioGroup1: TRadioGroup;
    GroupBox1: TGroupBox;
    Edit1: TEdit;
    Button1: TButton;
    GroupBox2: TGroupBox;
    Edit2: TEdit;
    StringGrid1: TStringGrid;
    procedure Button1Click(Sender: TObject);
    //procedure Button2Click(Sender: TObject);
    //procedure Button3Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure RadioGroup1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations } 
   res: Pchar;
  end;

//var
  //Form1: TForm1;
var
  H: THandle=0;
  ChooseDirOrFile: function (AllowChooseFile: boolean; AllowChooseDir: boolean; FormCaption: Pchar):PChar;stdcall;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
//var FileDlg: TForm2;
begin
res:=ChooseDirOrFile(true,true,'Please, choose dir or file to represent application');
if(res<>nil)
  then Edit1.Text:=res;
{
FileDlg:=Tform2.Create(Application);
FileDlg.ShowModal();
if(FileDlg.ChosenFile<>nil)
  then Edit1.Text:=FileDlg.ChosenFile;
FileDlg.Free;
StrDispose(FileDlg.ChosenFile);
}
end;
{
procedure TForm1.Button2Click(Sender: TObject);
//var FileDlg: TForm2;
begin
res:=ChooseDirOrFile(true,true,'Please, choose dir or file in additional info');
if(res<>nil)
  then Edit2.Text:=res;

FileDlg:=Tform2.Create(Application);
FileDlg.ShowModal();
if(FileDlg.ChosenFile<>nil)
  then Edit2.Text:=FileDlg.ChosenFile;
FileDlg.Free;
StrDispose(FileDlg.ChosenFile);

end;

procedure TForm1.Button3Click(Sender: TObject);
//var FileDlg: TForm2;
begin
res:=ChooseDirOrFile(false,true,'Please, choose working directory');
if(res<>nil)
  then Edit3.Text:=res;
end;
}
procedure TForm1.Button5Click(Sender: TObject);
var
contents: string;
temp: pchar;
begin
//<RunPlugin>service</RunPlugin>
{
contents:='<app>'+Edit1.text+'</app><way>'+Edit2.Text+'</way><dir>'+Edit3.Text+
'</dir><launch>'+ComboBox1.Text+'</launch><action>'+ComboBox2.Text+'</action>'+
'<monitor>'+booltostr(checkbox1.checked,TRUE)+'</monitor>';}
temp:=pchar(contents);
res:=StrAlloc(strlen(temp)+1);
StrCopy(res,temp);
Close();
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
res:=nil;
Close();
end;


procedure TForm1.FormDestroy(Sender: TObject);
begin
if(res<>nil)then StrDispose(res);
FreeLibrary(H);
end;

procedure TForm1.FormCreate(Sender: TObject);
var
lib: string;
begin  //  {
lib:=ExtractFileDir(Application.ExeName)+'\plugins\common\ChooseFileDlg.dll';
H:=LoadLibrary(pchar(lib));
if (H=0) then
begin
  MessageBox(Application.Handle,pchar('Library in "'+lib+'" could not be loaded!'),'Error',MB_ICONERROR);
  Halt(2);
end;
ChooseDirOrFile:=GetProcAddress(H,'ChooseDirOrFile');     //   }
lib:=ExtractFileDir(Application.ExeName);
StringGrid1.Cols[0].LoadFromFile(lib+'\plugins\mysql\options_names.txt');
end;

procedure TForm1.RadioGroup1Click(Sender: TObject);
begin
if(RadioGroup1.ItemIndex=0)then
begin
  GroupBox1.Show();
  GroupBox2.Hide();
end
else
begin
    GroupBox1.Hide();
    GroupBox2.Top:=GroupBox1.Top;
    GroupBox2.Show();
end;
end;

end.
