#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>

#include "prog/game.h"

//lcom_run proj

int main(int argc, char *argv[]) {

  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lessons/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lessons/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (proj_main_loop)(int argc, char *argv[]) {

    //preparar para começar o jogo
    if(const_buffer_frame(VBE_600)){           
        fprintf(stderr, "Error: %s\n", "const_buffer_frame function error.");
        return 1;
    }

    if(modo_grafico(VBE_600)){         //coloca no modo gráfico o minix no modo indexado
        fprintf(stderr, "Error: %s\n", "modo_grafico function error.");
        return 1;
    }

    alocar_sprite_mem();
    criarBufferSetDesenho();

    //começar o jogo
    if(loop_interrupcoes()){      //verifica se já foi pressionado a tecla ESC para sair
        fprintf(stderr, "Error: %s\n", "video_test_xpm function error.");
        return 1;
    }

    //voltar ao modo de texto (repor as alterações feitas no modo gráfico)
    if(vg_exit()){      //função da LCF que coloca no modo de texto
        fprintf(stderr, "Error: %s\n", "vg_exit function error.");
        return 1;
    }

    remover_sprite_mem();

  
    return 0;
}


