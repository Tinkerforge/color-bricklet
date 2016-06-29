Imports System
Imports Tinkerforge

Module ExampleThreshold
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change to your UID

    ' Callback subroutine for color reached callback
    Sub ColorReachedCB(ByVal sender As BrickletColor, ByVal r As Integer, ByVal g As Integer, _
                       ByVal b As Integer, ByVal c As Integer)
        Console.WriteLine("Color[R]: " + r.ToString())
        Console.WriteLine("Color[G]: " + g.ToString())
        Console.WriteLine("Color[B]: " + b.ToString())
        Console.WriteLine("Color[C]: " + c.ToString())
        Console.WriteLine("")
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim c As New BrickletColor(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Get threshold callbacks with a debounce time of 10 seconds (10000ms)
        c.SetDebouncePeriod(10000)

        ' Register color reached callback to subroutine ColorReachedCB
        AddHandler c.ColorReached, AddressOf ColorReachedCB

        ' Configure threshold for color "greater than 100, 200, 300, 400"
        c.SetColorCallbackThreshold(">"C, 100, 0, 200, 0, 300, 0, 400, 0)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
