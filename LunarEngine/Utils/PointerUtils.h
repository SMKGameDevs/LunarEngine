/*Copyright (C) MydnyteWolfy | 2026
 Origin Date: October 18, 2026
 --- File Start --- */

 #include <stdlib.h>
 #include <memory>

 namespace Lunar
 {
    template<typename Base, typename Cast>
    static std::unique_ptr<Cast> MakeNewUniquePtr(std::unique_ptr<Base> p_Ptr)
    {
        //Check that cast is allowed
        if(Cast* RawCastPtr = dynamic_cast<Cast*>(p_Ptr.get()))
        {
            p_Ptr.release();
            std::unique_ptr<Cast> CastPtr(RawCastPtr);
            
            return CastPtr;
        }
        else
        {
            return nullptr;
        }
    }
 }