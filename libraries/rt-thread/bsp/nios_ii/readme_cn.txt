1. �����淽������һ���հ�Nios II����.
2. ��ӱ�Ŀ¼������Դ�����ͷ�ļ�,�����RT-Thread�ں˼�Nios II CPU����Ҫ���ļ�.
��rt-thread
   ��
   ����include
   ��      rtdef.h
   ��      rthw.h
   ��      rtm.h
   ��      rtthread.h
   ��
   ����libcpu
   ��  ����nios
   ��      ����nios_ii
   ��              context_gcc.S
   ��              interrupt.c
   ��              stack.c
   ��              vector.S
   ��
   ����src
           clock.c
           device.c
           idle.c
           ipc.c
           irq.c
           kservice.c
           kservice.h
           mem.c
           mempool.c
           object.c
           rtm.c
           scheduler.c
           SConscript
           slab.c
           thread.c
           timer.c
3. ���ͷ�ļ�����·��
4. ������Ҫ�޸�rtconfig.h (Ĭ��Ϊ�����ں�)
