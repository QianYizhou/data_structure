#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "polynomial_calc.h"

//#define ENABLE_INPUT

//typedef struct PolyNode *Polynomial;
struct PolyNode {
    int coef;
    int expon;
    Polynomial link;
};
struct PolyMgr {
    Polynomial front;
    Polynomial rear;
    int size;
};

static char m_printBuf[BUFSIZ];


Polynomial  Polynomial_Create( void )
{
    Polynomial head = (Polynomial)malloc(sizeof(struct PolyNode));
    if ( NULL == head ) {
        perror( "malloc failed" );
    }

    head ->link = NULL;
    return head;
}

void        Polynomial_Decreate( Polynomial p )
{
}
/* add a item */
//void        Polynomial_Add( Polynomial p, int coef, int expon )
//{
//    Polynomial node = (Polynomial)malloc(sizeof(struct PolyNode));
//    if ( NULL == node ) {
//        perror( "malloc failed" );
//    }
//    node ->coef     = coef;
//    node ->expon    = expon;
//
//}
/* remove a item, and return its ptr */
/* need to free by user */
Polynomial  Polynomial_Del( Polynomial p );
int         Polynomial_IsEmpty( Polynomial p );
int         Polynomial_IsFull( Polynomial p );

void        Polynomial_Attach( int coef, int expon, struct PolyMgr *mgr )
{
    struct PolyNode *pNode = malloc( sizeof(struct PolyNode) );
    if ( NULL == pNode ) {
        perror( "malloc failed!" );
        return;
    }

    pNode ->coef = coef;
    pNode ->expon = expon;
    pNode ->link = NULL;

    mgr ->size ++;
    if ( 1 == mgr ->size ) {
        mgr ->front = pNode;
        mgr ->rear = pNode;
    } else {
        mgr ->rear ->link = pNode;
        mgr ->rear = pNode;
    }
}

//FIXME: unify printf and snprintf with to same form
void        Polynomial_Print( struct PolyMgr *mgr )
{
    int i = 0;
    if ( NULL == mgr ) {
        printf( "mgr is invalid\n" );
        return;
    }
    printf( "%d", mgr ->size );

    Polynomial tmp = mgr ->front;
    if ( NULL == tmp ) {
        printf( " 0" );
    }

    while ( tmp ) {
        printf( " %d %d", tmp ->coef, tmp ->expon );
        tmp = tmp ->link;
        ++i;
    }
    printf( "\n" );
}

const char *Polynomial_Print_String( struct PolyMgr *mgr )
{
#if 0
    char *buf_ptr = m_printBuf;

    if ( NULL == mgr ) {
        printf( "mgr is invalid\n" );
        return NULL;
    }

    memset( m_printBuf, 0, BUFSIZ );

    snprintf( m_printBuf, BUFSIZ, "%d", mgr ->size );
    printf( "%s\n", m_printBuf );

    Polynomial tmp = mgr ->front;
    while ( tmp ) {
        while ( *(++buf_ptr) ) {
        }
        snprintf( buf_ptr, BUFSIZ, " %d %d"
                , tmp ->coef, tmp ->expon );
        printf( "%s\n", m_printBuf );

        tmp = tmp ->link;
    }
#else
    char tmp_buf[BUFSIZ];

    if ( NULL == mgr ) {
        printf( "mgr is invalid\n" );
        return NULL;
    }

    memset( m_printBuf, 0, BUFSIZ );

    snprintf( m_printBuf, BUFSIZ, "%d", mgr ->size );
    //printf( "%s\n", m_printBuf );

    Polynomial tmp = mgr ->front;
    if ( NULL == tmp ) {
        strncat( m_printBuf, " 0", BUFSIZ );
        //printf( " 0" );
    }
    
    while ( tmp ) {
        snprintf( tmp_buf, BUFSIZ, " %d %d"
                , tmp ->coef, tmp ->expon );
        strncat( m_printBuf, tmp_buf, BUFSIZ );
        //printf( "%s\n", m_printBuf );

        tmp = tmp ->link;
    }
#endif

    //printf( "%s\n", m_printBuf );
    return m_printBuf;
}

struct PolyMgr * Polynomial_CreateMgr( void )
{
    struct PolyMgr *mgr = malloc( sizeof(struct PolyMgr) );
    if ( NULL == mgr ) {
        perror( "malloc PolyMgr failed" );
        return NULL;
    }
    mgr ->front = mgr ->rear = NULL;
    mgr ->size = 0;

    return mgr;
}

void            Polynomial_DecreateMgr( struct PolyMgr *mgr )
{
    int i = 0;

    if ( NULL == mgr ) {
        return;
    }

    Polynomial tmp = NULL;
    while ( (tmp = mgr ->front) ) {
        mgr ->front = tmp ->link;
        printf( "free. index: %d, coef: %d, expon: %d\n"
                , ++i, tmp ->coef, tmp ->expon );
        free( tmp );
    }

    free( mgr );
}

struct PolyMgr *
            Polynomial_CreateMgr_FromString( const char * str )
{
    int32_t num;
    int32_t i;
    char buf[512];

    struct PolyMgr *mgr = Polynomial_CreateMgr();
    if ( NULL == mgr ) {
        printf( "Polynomial_CreateMgr failed\n" );
        return NULL;
    }

    strcpy( buf, str );

    sscanf( buf, "%d%[^\n]", &num, buf );

    int coef; int expon;
    for (i = 0; i < num; i++) {
        sscanf( buf, " %d %d%[^\n]", &coef, &expon, buf );
        Polynomial_Attach( coef, expon, mgr );
    }

    Polynomial_Print( mgr );

    return mgr;
    //Polynomial_DecreateMgr( mgr );
}

struct PolyMgr *
            Polynomial_CreateMgr_FromInput( void )
{
    int32_t num;
    int32_t i;

    struct PolyMgr *mgr = Polynomial_CreateMgr();
    if ( NULL == mgr ) {
        printf( "Polynomial_CreateMgr failed\n" );
        return NULL;
    }

    scanf( "%d", &num );

    int coef; int expon;
    for (i = 0; i < num; i++) {
        scanf( " %d %d", &coef, &expon );
        Polynomial_Attach( coef, expon, mgr );
    }

    return mgr;
}

struct PolyMgr *
            Polynomial_Add( 
                    const struct PolyMgr *p1, 
                    const struct PolyMgr *p2 )
{
    struct PolyMgr *mgr = Polynomial_CreateMgr();
    Polynomial tmp1, tmp2;

    if ( NULL == mgr ) {
        printf( "Polynomial_CreateMgr failed\n" );
        return NULL;
    }

    if ( NULL == p1 || NULL == p2 ) {
        printf( "input param invalid\n" );
        return NULL;
    }

    tmp1 = p1 ->front;
    tmp2 = p2 ->front;

    while ( tmp1 && tmp2 ) {
        if ( tmp1 ->expon > tmp2 ->expon ) {
            Polynomial_Attach( tmp1 ->coef, tmp1 ->expon, mgr );
            tmp1 = tmp1 ->link;
        } else if ( tmp1 ->expon < tmp2 ->expon ) {
            Polynomial_Attach( tmp2 ->coef, tmp2 ->expon, mgr );
            tmp2 = tmp2 ->link;
        } else {
            Polynomial_Attach( tmp1 ->coef + tmp2 ->coef,
                    tmp1 ->expon, mgr );
            tmp1 = tmp1 ->link;
            tmp2 = tmp2 ->link;
        }
    }

    while ( tmp1 ) {
        Polynomial_Attach( tmp1 ->coef, tmp1 ->expon, mgr );
        tmp1 = tmp1 ->link;
    }
    while ( tmp2 ) {
        Polynomial_Attach( tmp2 ->coef, tmp2 ->expon, mgr );
        tmp2 = tmp2 ->link;
    }

    return mgr;
}

void    Polynomial_AddTo( 
        struct PolyMgr *p1, 
        const struct PolyMgr *p2 )
{
    /*
     * simple one
     */
    struct PolyMgr *mgr = Polynomial_Add( p1, p2 );

    p1 ->front = mgr ->front;
    p1 ->rear = mgr ->rear;
    p1 ->size = mgr ->size;

    Polynomial_DecreateMgr( p1 );
#if 0
    struct PolyMgr *mgr = Polynomial_CreateMgr();
    Polynomial tmp1, tmp2;

    if ( NULL == mgr ) {
        printf( "Polynomial_CreateMgr failed\n" );
        return NULL;
    }
#endif

    if ( NULL == p1 || NULL == p2 ) {
        printf( "input param invalid\n" );
        return NULL;
    }


    tmp1 = p1 ->front;
    tmp2 = p2 ->front;

    //FIXME: modify front and rear of p1
    
    while ( tmp1 && tmp2 ) {
        if ( tmp1 ->expon > tmp2 ->expon ) {
            //Polynomial_Attach( tmp1 ->coef, tmp1 ->expon, mgr );
            tmp1 = tmp1 ->link;
        } else if ( tmp1 ->expon < tmp2 ->expon ) {
            //Polynomial_Attach( tmp2 ->coef, tmp2 ->expon, mgr );

            /*
             * malloc and add
             */
            struct PolyNode *pNode = malloc( sizeof(struct PolyNode) );
            if ( NULL == pNode ) {
                perror( "malloc failed!" );
                return;
            }

            pNode ->coef = tmp2 ->coef;
            pNode ->expon = tmp2 ->expon;
            pNode ->link = tmp ->link;

            tmp1 ->link = pNode;

            p1 ->size ++;

            tmp1 = pNode ->link;

            /*
             * next tmp2 
             */
            tmp2 = tmp2 ->link;
        } else {
            //Polynomial_Attach( tmp1 ->coef + tmp2 ->coef,
            //        tmp1 ->expon, mgr );
            tmp1 ->coef += tmp2 ->coef;

            tmp1 = tmp1 ->link;
            tmp2 = tmp2 ->link;
        }
    }

    //while ( tmp1 ) {
    //    Polynomial_Attach( tmp1 ->coef, tmp1 ->expon, mgr );
    //    tmp1 = tmp1 ->link;
    //}
    while ( tmp2 ) {
        Polynomial_Attach( tmp2 ->coef, tmp2 ->expon, p1 );
        tmp2 = tmp2 ->link;
    }

    //return mgr;
}

struct PolyMgr *
            Polynomial_Multi(
                    const struct PolyMgr *p1,
                    const struct PolyMgr *p2 )
{
    struct PolyMgr *mgr = Polynomial_CreateMgr();
    Polynomial tmp1, tmp2;

    if ( NULL == mgr ) {
        printf( "Polynomial_CreateMgr failed\n" );
        return NULL;
    }

    if ( NULL == p1 || NULL == p2 ) {
        printf( "input param invalid\n" );
        return NULL;
    }

    while ( (tmp1 = p1 ->front) ) {
        struct PolyMgr *m1 = Polynomial_CreateMgr();
        if ( NULL == m1 ) {
            printf( "Polynomial_CreateMgr failed\n" );
            return NULL;
        }

        while ( (tmp2=p2 ->front) ) {
            Polynomial_Attach( 
                    tmp1 ->coef * tmp2 ->coef,
                    tmp1 ->expon + tmp2 ->expon,
                    m1 );

#if 1
            tmp = Polynomial_Add( mgr, m1 );
            Polynomial_DecreateMgr( mgr );
            mgr = tmp;
#else
            Polynomial_AddTo( mgr, m1 );
#endif
        }

        Polynomial_DecreateMgr( m1 );
    }

    return mgr;
}

