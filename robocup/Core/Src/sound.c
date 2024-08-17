#include "sound.h"

void sound_init(){
    HAL_GPIO_WritePin(IO_0_GPIO_Port,IO_0_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_1_GPIO_Port,IO_1_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_2_GPIO_Port,IO_2_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_3_GPIO_Port,IO_3_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_4_GPIO_Port,IO_4_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_5_GPIO_Port,IO_5_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_6_GPIO_Port,IO_6_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_7_GPIO_Port,IO_7_Pin,GPIO_PIN_SET);
}

void sound_play(int a){
    if(a==1){ //播放第一首曲 “准备完毕” 00001.mp3
        HAL_GPIO_WritePin(IO_0_GPIO_Port,IO_0_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IO_1_GPIO_Port,IO_1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_2_GPIO_Port,IO_2_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_3_GPIO_Port,IO_3_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_4_GPIO_Port,IO_4_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_5_GPIO_Port,IO_5_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_6_GPIO_Port,IO_6_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_7_GPIO_Port,IO_7_Pin,GPIO_PIN_SET);
        HAL_Delay(30);
        HAL_GPIO_WritePin(IO_0_GPIO_Port,IO_0_Pin,GPIO_PIN_SET);
    }
    else if(a==2){//播放第二首曲目 “到达指定景点” 00002.mp3
        HAL_GPIO_WritePin(IO_0_GPIO_Port,IO_0_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_1_GPIO_Port,IO_1_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IO_2_GPIO_Port,IO_2_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_3_GPIO_Port,IO_3_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_4_GPIO_Port,IO_4_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_5_GPIO_Port,IO_5_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_6_GPIO_Port,IO_6_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_7_GPIO_Port,IO_7_Pin,GPIO_PIN_SET);
        HAL_Delay(30);
        HAL_GPIO_WritePin(IO_1_GPIO_Port,IO_1_Pin,GPIO_PIN_SET);
    }
    else if(a == 3){//"到达二号平台"
        HAL_GPIO_WritePin(IO_0_GPIO_Port,IO_0_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_1_GPIO_Port,IO_1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_2_GPIO_Port,IO_2_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IO_3_GPIO_Port,IO_3_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_4_GPIO_Port,IO_4_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_5_GPIO_Port,IO_5_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_6_GPIO_Port,IO_6_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_7_GPIO_Port,IO_7_Pin,GPIO_PIN_SET);
        HAL_Delay(30);        
        HAL_GPIO_WritePin(IO_2_GPIO_Port,IO_2_Pin,GPIO_PIN_SET);

    }
    else if(a == 3){//"到达三号平台"
        HAL_GPIO_WritePin(IO_0_GPIO_Port,IO_0_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_1_GPIO_Port,IO_1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_2_GPIO_Port,IO_2_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_3_GPIO_Port,IO_3_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IO_4_GPIO_Port,IO_4_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_5_GPIO_Port,IO_5_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_6_GPIO_Port,IO_6_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_7_GPIO_Port,IO_7_Pin,GPIO_PIN_SET);  
        HAL_Delay(30);        
        HAL_GPIO_WritePin(IO_3_GPIO_Port,IO_3_Pin,GPIO_PIN_SET);      
    }
    else if(a == 4){//'到达四号'
        HAL_GPIO_WritePin(IO_0_GPIO_Port,IO_0_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_1_GPIO_Port,IO_1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_2_GPIO_Port,IO_2_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_3_GPIO_Port,IO_3_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_4_GPIO_Port,IO_4_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IO_5_GPIO_Port,IO_5_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_6_GPIO_Port,IO_6_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IO_7_GPIO_Port,IO_7_Pin,GPIO_PIN_SET);
        HAL_Delay(30);        
        HAL_GPIO_WritePin(IO_4_GPIO_Port,IO_4_Pin,GPIO_PIN_SET);
    }
    else if(a == 5){//'到达五号号'
    HAL_GPIO_WritePin(IO_0_GPIO_Port,IO_0_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_1_GPIO_Port,IO_1_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_2_GPIO_Port,IO_2_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_3_GPIO_Port,IO_3_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_4_GPIO_Port,IO_4_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_5_GPIO_Port,IO_5_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IO_6_GPIO_Port,IO_6_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_7_GPIO_Port,IO_7_Pin,GPIO_PIN_SET);
    HAL_Delay(30);        
    HAL_GPIO_WritePin(IO_5_GPIO_Port,IO_5_Pin,GPIO_PIN_SET);
}
else if(a == 6){//'到达六号'
    HAL_GPIO_WritePin(IO_0_GPIO_Port,IO_0_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_1_GPIO_Port,IO_1_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_2_GPIO_Port,IO_2_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_3_GPIO_Port,IO_3_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_4_GPIO_Port,IO_4_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_5_GPIO_Port,IO_5_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_6_GPIO_Port,IO_6_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IO_7_GPIO_Port,IO_7_Pin,GPIO_PIN_SET);
    HAL_Delay(30);        
    HAL_GPIO_WritePin(IO_6_GPIO_Port,IO_6_Pin,GPIO_PIN_SET);
}
else if(a == 7){//'到达八号'
    HAL_GPIO_WritePin(IO_0_GPIO_Port,IO_0_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_1_GPIO_Port,IO_1_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_2_GPIO_Port,IO_2_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_3_GPIO_Port,IO_3_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_4_GPIO_Port,IO_4_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_5_GPIO_Port,IO_5_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_6_GPIO_Port,IO_6_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_7_GPIO_Port,IO_7_Pin,GPIO_PIN_RESET);
    HAL_Delay(30);        
    HAL_GPIO_WritePin(IO_7_GPIO_Port,IO_7_Pin,GPIO_PIN_SET);
}
}
