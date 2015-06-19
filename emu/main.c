#include <stdio.h>
#include <stdlib.h>
#include <emu/cpu.h>

static void iset(emu_cpu* cpu)
{
  printf("calling iset!\n");
  //first arg is byte value
  //second arg is target address
    
}

static void imov(emu_cpu* cpu)
{
  printf("calling imov!\n");
  //first arg is source address
  //second arg is target address
}

static void iadd(emu_cpu* cpu)
{
  printf("calling iadd!\n");
  //first arg is source address
  //second arg is target address
}

static void iprn(emu_cpu* cpu)
{
  printf("calling iprn!\n");
  //first arg is address of value
}

static void ijmp(emu_cpu* cpu)
{
  printf("calling ijmp!\n");
  //first arg is target address
}

static void ijr(emu_cpu* cpu)
{
  printf("calling ijr!\n");
  //first arg is target offset
}

#define ISET 0
#define IMOV 1
#define IADD 2
#define IPRN 3
#define IJMP 4
#define IJR  5

int main(int argc, char** argv)
{
  emu_instruction it[0x100];
  int i = 0;
  for(; i < 0x100; i++) it[i] = NULL;
  it[IMOV] = imov;
  it[ISET] = iset;
  it[IADD] = iadd;
  it[IPRN] = iprn;
  it[IJMP] = ijmp;
  it[IJR ] = ijr;

  emu_device dev;
  dev.mem = emum_create(10000);
  for(i = 0; i < 10000; i++) ((uint8_t*)dev.mem->data)[i] = 0x00;
  emu_cpu cpu;
  cpu.dev = &dev;
  cpu.ip = 0;
  for(i = 0; i < 0x100; i++) cpu.it[i] = it[i];
  
  return 0;
}
