unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;//, unit2;
type
  TForm1 = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Edit1: TEdit;
    Button4: TButton;
    Button5: TButton;
    Memo1: TMemo;
//    procedure Button1Click(Sender: TObject);
//    procedure Button2Click(Sender: TObject);
//    procedure Button3Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
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
                         {
procedure TForm1.Button1Click(Sender: TObject);
var FileDlg: TForm2;
begin
FileDlg:=Tform2.Create(Application);
FileDlg.ShowModal();
if(FileDlg.ChosenFile<>nil)
  then Edit1.Text:=FileDlg.ChosenFile;
FileDlg.Free;
StrDispose(FileDlg.ChosenFile);
end;                      }
                     {
procedure TForm1.Button2Click(Sender: TObject);
var FileDlg: TForm2;
begin
FileDlg:=Tform2.Create(Application);
FileDlg.ShowModal();
if(FileDlg.ChosenFile<>nil)
  then Edit2.Text:=FileDlg.ChosenFile;
FileDlg.Free;
StrDispose(FileDlg.ChosenFile);
end;                  }
                            {
procedure TForm1.Button3Click(Sender: TObject);
var FileDlg: TForm2;
begin
FileDlg:=Tform2.Create(Application);
FileDlg.ShowModal();
if(FileDlg.ChosenFile<>nil)
  then Edit3.Text:=FileDlg.ChosenFile;
FileDlg.Free;
StrDispose(FileDlg.ChosenFile);
end;                         }

procedure TForm1.Button5Click(Sender: TObject);
var
contents: string;
temp: pchar;
i: integer;
begin
  contents:='<RunPlugin>service</RunPlugin><name>'+Edit1.text+'</name><Refresh>1000</Refresh>';
  if(not(memo1.Text='')) then
  begin
  contents:=contents+'<parameters>';
  for i:=0 to memo1.Lines.Count-1 do
    contents:=contents+'<param>'+memo1.Lines[i]+'</param>';
  contents:=contents+'</parameters>';
end;
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


procedure TForm1.FormDestroy(Sender: TObject);
begin
if(res<>nil)then StrDispose(res);
end;

end.
