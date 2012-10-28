unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;//, unit2;
type
  TForm1 = class(TForm)
    Button4: TButton;
    Button5: TButton;
    Label1: TLabel;
    Edit1: TEdit;
    CheckBox1: TCheckBox;
    GroupBox1: TGroupBox;
    CheckBox2: TCheckBox;
    CheckBox3: TCheckBox;
    CheckBox4: TCheckBox;
    GroupBox2: TGroupBox;
    CheckBox5: TCheckBox;
    CheckBox6: TCheckBox;
    CheckBox7: TCheckBox;
    CheckBox8: TCheckBox;
    CheckBox9: TCheckBox;
    CheckBox10: TCheckBox;
    CheckBox11: TCheckBox;
    Button1: TButton;
    Button2: TButton;
    Label2: TLabel;
    CheckBox12: TCheckBox;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
//    procedure Button3Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
//    procedure FormCreate(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
    procedure CheckBox12Click(Sender: TObject);
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
checkbox5.Checked:=true;
checkbox6.Checked:=true;
checkbox7.Checked:=true;
checkbox8.Checked:=true;
checkbox9.Checked:=true;
checkbox10.Checked:=true;
checkbox11.Checked:=true;
end;

procedure TForm1.Button2Click(Sender: TObject);
//var FileDlg: TForm2;
begin
checkbox5.Checked:=false;
checkbox6.Checked:=false;
checkbox7.Checked:=false;
checkbox8.Checked:=false;
checkbox9.Checked:=false;
checkbox10.Checked:=false;
checkbox11.Checked:=false;
end;


procedure TForm1.Button5Click(Sender: TObject);
var
contents: string;
temp: pchar;
begin
contents:='<RunPlugin>drives</RunPlugin>';
if((checkbox5.Checked)and(checkbox6.Checked)and(checkbox7.Checked)and(checkbox8.Checked)and(checkbox9.Checked)and(checkbox10.Checked)and(checkbox11.Checked))
then contents:=contents+'<Drives>ALL</Drives>'
else
begin
  contents:=contents+'<Drives>';
  if(checkbox5.Checked)then contents:=contents+'<Drive>DRIVE_UNKNOWN</Drive>';
  if(checkbox6.Checked)then contents:=contents+'<Drive>DRIVE_NO_ROOT_DIR</Drive>';
  if(checkbox7.Checked)then contents:=contents+'<Drive>DRIVE_REMOVABLE</Drive>';
  if(checkbox8.Checked)then contents:=contents+'<Drive>DRIVE_FIXED</Drive>';
  if(checkbox9.Checked)then contents:=contents+'<Drive>DRIVE_REMOTE</Drive>';
  if(checkbox10.Checked)then contents:=contents+'<Drive>DRIVE_CDROM</Drive>';
  if(checkbox11.Checked)then contents:=contents+'<Drive>DRIVE_RAMDISK</Drive>';
  contents:=contents+'</Drives>';
end;
if(checkbox12.Checked)then contents:=contents+'<Refresh>'+Edit1.text+'</Refresh>'
else contents:=contents+'<Refresh>0</Refresh>';
contents:=contents+'<ShowVolName>'+booltostr(checkbox2.checked,TRUE)+'</ShowVolName>';
contents:=contents+'<ShowVolIcon>'+booltostr(checkbox3.checked,TRUE)+'</ShowVolIcon>';
contents:=contents+'<ShowVolSpace>'+booltostr(checkbox4.checked,TRUE)+'</ShowVolSpace>';
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
end;


procedure TForm1.CheckBox1Click(Sender: TObject);
begin
if(checkbox1.Checked)then edit1.Enabled:=false
else edit1.Enabled:=true;
end;

procedure TForm1.CheckBox12Click(Sender: TObject);
begin
if(checkbox12.Checked)then
begin
  edit1.Enabled:=true;
  checkbox1.Enabled:=true;
end
else
begin
  edit1.Enabled:=false;
  checkbox1.Enabled:=false;
end;
end;

end.
