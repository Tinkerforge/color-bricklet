Imports Tinkerforge

Module ExampleSimple
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "abc" ' Change to your UID

    ' Callback function for color callback (in RGBC)
    Sub ColorCB(ByVal sender As BrickletColor, ByVal r As Integer, _
                ByVal g As Integer, ByVal b As Integer, ByVal cl As Integer)
                
        System.Console.WriteLine("Color(R, G, B, C): " + r.ToString() _
        + ", " + g.ToString() + ", " + b.ToString() + ", " + cl.ToString())
        System.Console.WriteLine("")
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim c As New BrickletColor(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Set Period for color callback to 1s (1000ms)
        ' Note: The color callback is only called every second if the 
        '       color has changed since the last call!
        c.SetColorCallbackPeriod(1000)

        ' Register color callback to function ColorCB
        AddHandler c.Color, AddressOf ColorCB

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadKey()
        ipcon.Disconnect()
    End Sub
End Module
