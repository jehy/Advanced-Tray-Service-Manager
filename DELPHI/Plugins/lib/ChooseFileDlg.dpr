library ChooseFileDlg;

{ Important note about DLL memory management: ShareMem must be the
  first unit in your library's USES clause AND your project's (select
  Project-View Source) USES clause if your DLL exports any procedures or
  functions that pass strings as parameters or function results. This
  applies to all strings passed to and from your DLL--even those that
  are nested in records and classes. ShareMem is the interface unit to
  the BORLNDMM.DLL shared memory manager, which must be deployed along
  with your DLL. To avoid using BORLNDMM.DLL, pass string information
  using PChar or ShortString parameters. }

uses
  SysUtils,
  Forms,
  Classes,
  Unit2 in 'Unit2.pas' {Form2};
  //Unit1 in '..\..\..\..\..\..\..\Program Files\Borland\Delphi7\Projects\Unit1.pas' {Form1};

//{$R *.res}
//var res0: Pchar;

function ChooseDirOrFile (AllowChooseFile: boolean; AllowChooseDir: boolean; FormCaption: Pchar):PChar;stdcall;
var
  myform: TForm2;
  caption: string;
begin
myform:=TForm2.Create(Application);
if(not(AllowChooseFile))then
begin
  myform.Button2.Visible:=false;
  myform.DenyChooseFile:=true;
end;
if (not(AllowChooseDir))then myform.Button1.Visible:=false;
if(not(FormCaption=nil))then
begin
  caption:=FormCaption;
  myform.Caption:=caption;
end;
myform.ShowModal();
//res0:=res;
//result:=myform.res;
result:=myform.ChosenFile;
myform.Free();
end;

exports
  ChooseDirOrFile;
end.
