library command_vis;

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
  Unit1 in 'Unit1.pas' {Form1};
  //Unit2 in 'Unit2.pas' {Form2};

//{$R *.res}
//var res0: Pchar;

function DlgNewItem ():PChar;stdcall;
var
  myform: TForm1;
begin
myform:=TForm1.Create(Application);
myform.ShowModal();
//res0:=res;
//result:=myform.res;
if(myform.res<>nil) then
begin
  result:=StrAlloc(strlen(myform.res)+1);
  StrCopy(result,myform.res);
end
else
begin
    result:=StrAlloc(7);
    StrCopy(result,'cancel');
end;
myform.Free();
end;

exports
  DlgNewItem;
end.
