program ExampleSimple;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickletColor;

type
  TExample = class
  private
    ipcon: TIPConnection;
    c: TBrickletColor;
  public
    procedure ColorCB(sender: TBrickletColor;
                      const r: Word; const g: Word;
                      const b: Word; const cl: Word);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'abc'; { Change to your UID }

var
  e: TExample;

{ Callback function for color callback }
procedure TExample.ColorCB(sender: TBrickletColor;
                           const r: Word;
                           const g: Word;
                           const b: Word;
                           const cl: Word);
begin
    WriteLn(Format('Color(R): %u', [r]));
    WriteLn(Format('Color(G): %u', [g]));
    WriteLn(Format('Color(B): %u', [b]));
    WriteLn(Format('Color(C): %u', [cl]));
    WriteLn('');
end;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  c := TBrickletColor.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Set Period for color callback to 1s (1000ms)
    Note: The callback is only called every second if the
          color has changed since the last call! }
  c.SetColorCallbackPeriod(1000);

  { Register color callback to procedure ColorCB }
  c.OnColor := {$ifdef FPC}@{$endif}ColorCB;

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
