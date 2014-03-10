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
    procedure ReachedCB(sender: TBrickletColor;
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

{ Callback for color threshold reached }
procedure TExample.ReachedCB(sender: TBrickletColor; const r: word;
                             const g: word; const b: word;
                             const cl: word);
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

  { Get threshold callbacks with a debounce time of 10 seconds (10000ms) }
  c.SetDebouncePeriod(10000);

  { Register threshold reached callback to procedure ReachedCB }
  c.OnColorReached := {$ifdef FPC}@{$endif}ReachedCB;

  { Configure threshold for color values,
    RED  : greater than 100
    GREEN: greater than 200
    BLUE : greater than 300
    CLEAR: greater than 400 }
  c.SetColorCallbackThreshold('>', 0, 100, 0, 200, 0, 300, 0, 400);

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
