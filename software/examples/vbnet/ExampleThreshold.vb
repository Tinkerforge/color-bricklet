Imports Tinkerforge

Module ExampleSimple
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "abc" ' Change to your UID

    ' Callback for humidity outside of 30 to 60 %RH
    Sub ReachedCB(ByVal sender As BrickletColor, ByVal r As Integer, _
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

        ' Get threshold callbacks with a debounce time of 10 seconds (10000ms)
        c.SetDebouncePeriod(10000)

        ' Register threshold reached callback to function ReachedCB
        AddHandler c.ColorReached, AddressOf ReachedCB

        ' Configure threshold for color values,
        ' RED  : greater than 100
        ' GREEN: greater than 200
        ' BLUE : greater than 300
        ' CLEAR: greater than 400
        c.SetColorCallbackThreshold(">"C, 0, 100, 0, 200, 0, 300, 0, 400)

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadKey()
        ipcon.Disconnect()
    End Sub
End Module
