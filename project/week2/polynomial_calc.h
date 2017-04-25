#pragma once

#ifdef  __cplusplus
extern "C"
{
#endif//__cplusplus

typedef struct PolyNode *Polynomial;

struct PolyMgr;

Polynomial  Polynomial_Create( void );
void        Polynomial_Decreate( Polynomial p );
/* add a item */
//void        Polynomial_Add( Polynomial p, int coef, int expon );
/* remove a item, and return its ptr */
/* need to free by user */
Polynomial  Polynomial_Del( Polynomial p );
int         Polynomial_IsEmpty( Polynomial p );
int         Polynomial_IsFull( Polynomial p );

void        Polynomial_Attach( int coef, int expon, struct PolyMgr *mgr );

struct PolyMgr * 
            Polynomial_CreateMgr( void );
void        Polynomial_DecreateMgr( struct PolyMgr *mgr );
void        Polynomial_Print( struct PolyMgr *mgr );
const char *Polynomial_Print_String( struct PolyMgr *mgr );

struct PolyMgr *
            Polynomial_CreateMgr_FromInput( void );
struct PolyMgr *
            Polynomial_CreateMgr_FromString( const char * str );

struct PolyMgr *
            Polynomial_Add( 
                    const struct PolyMgr *p1, 
                    const struct PolyMgr *p2 );
struct PolyMgr *
            Polynomial_Multi(
                    const struct PolyMgr *p1,
                    const struct PolyMgr *p2 );

struct PolyMgr *
            Polynomial_AddTo( 
                    struct PolyMgr *p1, 
                    const struct PolyMgr *p2 );

#ifdef  __cplusplus
}
#endif//__cplusplus
