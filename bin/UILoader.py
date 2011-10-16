from UI import *
from Engine import *

def GetRoot():
    engine = MyEngine()
    
    img = UIImage(
        None,
        500, 750 )

    img.LoadImage( "pic1.jpg" )

    return img
