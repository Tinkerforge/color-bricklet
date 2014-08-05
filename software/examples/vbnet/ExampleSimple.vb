Imports Tinkerforge

Module ExampleSimple
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "abc" ' Change to your UID

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim c As New BrickletColor(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Get current colot (in RGBC)
        Dim r As Short
        Dim g As Short
        Dim b As Short
        Dim cl As Short
        c.GetColor(r, g, b, cl)

        System.Console.WriteLine("Color(R): " + r.ToString())
        System.Console.WriteLine("Color(G): " + g.ToString())
        System.Console.WriteLine("Color(B): " + b.ToString())
        System.Console.WriteLine("Color(C): " + cl.ToString())

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadKey()
        ipcon.Disconnect()
    End Sub
End Module
