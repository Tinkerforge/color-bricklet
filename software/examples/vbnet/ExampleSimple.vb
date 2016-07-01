Imports System
Imports Tinkerforge

Module ExampleSimple
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Color Bricklet

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim c As New BrickletColor(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Get current color
        Dim r As Integer
        Dim g As Integer
        Dim b As Integer
        Dim c_ As Integer

        c.GetColor(r, g, b, c_)

        Console.WriteLine("Color[R]: " + r.ToString())
        Console.WriteLine("Color[G]: " + g.ToString())
        Console.WriteLine("Color[B]: " + b.ToString())
        Console.WriteLine("Color[C]: " + c_.ToString())

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
