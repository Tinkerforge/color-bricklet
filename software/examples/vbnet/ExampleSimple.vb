Imports Tinkerforge

Module ExampleSimple
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change to your UID

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim c As New BrickletColor(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Get current color
        Dim r As Integer
        Dim g As Integer
        Dim b As Integer
        Dim cl As Integer

        c.GetColor(r, g, b, cl)

        System.Console.WriteLine("Color(R): " + r.ToString())
        System.Console.WriteLine("Color(G): " + g.ToString())
        System.Console.WriteLine("Color(B): " + b.ToString())
        System.Console.WriteLine("Color(C): " + cl.ToString())

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
