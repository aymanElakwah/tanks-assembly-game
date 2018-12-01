.include loadinterface.inc
.model small
.data



Startinterface   db    '      _________       _______        _              _              _______      '
                 db    '      \__   __/      (  ___  )      ( (    /|      | \    /\      (  ____ \     '
                 db    '         ) (         | (   ) |      |  \  ( |      |  \  / /      | (    \/     '
                 db    '         | |         | (___) |      |   \ | |      |  (_/ /       | (_____      '
                 db    '         | |         |  ___  |      | (\ \) |      |   _ (        (_____  )     '
                 db    '         | |         | (   ) |      | | \   |      |  ( \ \             ) |     '
                 db    '         | |         | )   ( |      | )  \  |      |  /  \ \      /\____) |     '
                 db    '         )_(         |/     \|      |/    )_)      |_/    \/      \_______)     '
                 db    '                                                                                '
                 db    '                                                                                '
                 db    '                                                                                '
                 db    '                                                                                '
                 db    '                                                                                '
                 db    '                                                                                '
                 db    '                                                                                '
                 db    '                                                                                '
                 db    '                                                                                ' 
CHOOSEMODE       db    '                             ',16,' Normal  mode                                    '
                 db    '                                Network mode (Coming Soon)                          '
                 db    '                                                                                '
                 db    '                                                                                '
                 db    '                                                                                '
                 db    '                                                                                $'
                 
                 
      
.code



main proc far
    
    mov ax,@data
    mov ds,ax
   
    
    loadinterface
    
    
    
    main endp
end main
    
    
    
    
    
