
def GetRoot():   
    timer = Timer()     # 
    
    img = UIImage(
        None,
        500, 750 )

    img.LoadImage( "pic1.jpg" )

    Save( img )    

    tranni = TranslateUIAnimator(
        timer.GetRealTime(),
        3000,
        vector2d( 300, 200 )
        )
    img.AddAnimator( tranni )
    Save( tranni )              # 对于所有创建出来的对象都要使用Save，不用使用drop

    rotani = RotateUIAnimator(
        timer.GetRealTime(),
        3000,
        360,
        True
        )
    img.AddAnimator( rotani )
    Save( rotani )

    return img
