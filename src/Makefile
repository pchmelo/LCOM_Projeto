# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/dispositivos/
.PATH: ${.CURDIR}/dispositivos/teclado
.PATH: ${.CURDIR}/dispositivos/timer
.PATH: ${.CURDIR}/dispositivos/grafica
.PATH: ${.CURDIR}/dispositivos/rato
.PATH: ${.CURDIR}/assets/
.PATH: ${.CURDIR}/assets/cards
.PATH: ${.CURDIR}/assets/game_table
.PATH: ${.CURDIR}/assets/main_menu
.PATH: ${.CURDIR}/assets/mouse
.PATH: ${.CURDIR}/assets/numbers
.PATH: ${.CURDIR}/assets/connection
.PATH: ${.CURDIR}/prog/
.PATH: ${.CURDIR}/prog/functions
.PATH: ${.CURDIR}/prog/game_rules
.PATH: ${.CURDIR}/prog/process
.PATH: ${.CURDIR}/dispositivos/rtc
.PATH: ${.CURDIR}/dispositivos/sp

# source code files to be compiled
SRCS = proj.c grafica.c utils.c timer.c sprite.c mouse.c kbc.c composer.c teclado_process.c rato_process.c timer_process.c game.c rules.c collision.c rtc.c fila_sp.c sp.c serial_process.c aux_func.c interrupts.c handler.c aux_dispositivos.c

# additional compilation flags
CFLAGS += -I${.CURDIR}/recursos/sprites -pedantic -D_LCOM_OPTIMIZED_
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>