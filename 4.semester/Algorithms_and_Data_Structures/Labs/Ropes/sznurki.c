#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

#define MILION 1000000

inline int pop2(unsigned long long x);
unsigned long long result = 0;
uint32_t size;

unsigned long long pow2to[64];

typedef struct sznurek{
  unsigned long long dlugosc;
  unsigned long long kawalki;
} Sznurek;

Sznurek tab[MILION];

int wczytywanie(void);
int obrachunki(void);
int compare_function(const void *a,const void *b);
long long bin_search(unsigned long long key);
unsigned long long init_pow2to(void);
inline unsigned long long pow2(uint32_t i);

int main(void){

  init_pow2to();
  wczytywanie();

  qsort(tab, size, sizeof(Sznurek), compare_function);

  obrachunki();


  printf("%llu", result);


  return 0;
}

//==========================================================================

int wczytywanie(){//������ ���������


  unsigned long long length;
  unsigned long long pieces;

  scanf("%u", &size);
  for(uint32_t i = 0; i < size; i++){
    scanf("%llu %llu", &length, &pieces);
    tab[i].dlugosc = length;
    tab[i].kawalki = pieces;
  }

  return 0;
}

//==========================================================================

int obrachunki(void){
  for(uint32_t n = 0; n < size; n++){ //��������� ����� ������� �������� �������
    if((tab[n].kawalki)%2==1)//������� ��������
    {
      result++;
      (tab[n].kawalki)--;
    }
    for(uint32_t i = 1; tab[n].dlugosc>0 && i < sizeof(unsigned long long)*8; i++){//������� �� ��������� � ��������� x*(2^i)

        unsigned long long key = tab[n].dlugosc * pow2to[i];//������� ��������� ����
        unsigned long long index = bin_search(key);//������� ������ ��������� � ��������� ������
        tab[n].kawalki = (tab[n].kawalki)/2;//�������� ������
        if(index != -1){//������� � ����� ������ ����� � ����� �������

          tab[n].kawalki += tab[index].kawalki;
          tab[index].kawalki=0;
          tab[index].dlugosc=0;
          if(tab[n].kawalki%2==1)//������� ��������
          {
            result++;
            (tab[n].kawalki)--;
          }
        }
        else{//�������� � ����� ������ ��� ����� � �������
          result += pop2(tab[n].kawalki);//������� ������� ��� ��� ����� ������� ����� �������, ���� ���� ��������� ���� �� ����� ����� (��� ���� ���������)
          tab[n].kawalki=0;//�� ����������. ��� ���� �� ���������� ��� ������� � ����� ���������, ������ ���� �������� ��� �� �����
          break;
        }
    }
  }
  return 0;
}

//==========================================================================

int compare_function(const void *a,const void *b){//������ ���������
  unsigned long long adlugosc = *((unsigned long long *) a);
  unsigned long long bdlugosc = *((unsigned long long *) b);
  return adlugosc - bdlugosc;
}

//==========================================================================

long long bin_search(unsigned long long key)//������ ���� ������, ��� ���� ������ ���������
{
  unsigned long long low = 0;
  unsigned long long high = size-1;
  unsigned long long mid;

  while(low <= high){
    mid = (low + high)/2;
    if(tab[mid].dlugosc < key){
      low = mid + 1;
    }
    else if(tab[mid].dlugosc > key){
      high = mid-1;
    }
    else if(tab[mid].dlugosc == key)
    {
      return (long long)mid;
    }
  }

  return -1;
}

//==========================================================================

unsigned long long init_pow2to(void){//������ ���������
  for(uint32_t i = 0; i < sizeof(unsigned long long)*8; i++){
    pow2to[i] = pow2(i);
  }
  return 0;
}

//==========================================================================

inline unsigned long long pow2(uint32_t i){//������ ���������
  unsigned long long res = 1;
  while(i>0){
    i=i-1;
    res=res<<1;
  }
  return res;
}

//==========================================================================

inline int pop2(unsigned long long x)//������ ���������
{
    x = x - ((x >> 1) & 0x5555555555555555);
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0F;
    x = x + (x >> 8);
    x = x + (x >> 16);
    x = x + (x >> 32);
    return x & 0xFF;
}

//==========================================================================
