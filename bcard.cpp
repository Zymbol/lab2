//Student: Zachary Scholefield

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef 
int i;
typedef float f;
struct v {
    f xRay, yankee, zulu;
    v operator + (v r) {
        return v(xRay+r.xRay,yankee+r.yankee,zulu+r.zulu);
    }
    v operator*(f r) {
        return v (xRay*r,yankee*r,zulu*r);
    }
    f operator% (v r){
        return xRay*r.xRay+yankee*r.yankee+zulu*r.zulu;}v() {
        }
    v operator^(v r) {
        return v(yankee*r.zulu-zulu*r.yankee,zulu*r.xRay-xRay*r.zulu,xRay*r.yankee-yankee*r.xRay);
    }
    v (f a,f b,f c){
        xRay=a;         //changed x to xray for readabality
        yankee=b;       //changed y to yankee for readability
        zulu=c;         //changed z to zulu for readability
    }
    v operator!() {
        return *this* (1/sqrt(*this%*this));
    }
};
i G[]={0,418700, 69714,69714,140178, 70162, 70162, 418700, 0}; //Creates pic
f R() {                                                                     
    return(f)rand()/RAND_MAX;
}
i T(v o,v d,f&t,v&n) {          // Function T
    t=1e9;
    i m=0;
    f p=-o.zulu/d.zulu;
    if(.01<p)                   // if statement
        t=p, n=v(0, 0, 1), m=1;
    for (i k=19; k--;)           //for loop 
        for(i j=9; j--;)
            if(G[j]&1 << k) {
                v p=o+v(-k,0,-j-4);
                f b=p%d, c=p%p-1, q=b*b-c;
                if(q>0) {
                    f s =- b - sqrt(q);
                    if(s < t && s > .01)
                        t = s,
                            n= !(p+d*t),
                            m=2;
                }
            }
    return m;
}
v S(v o,v d) {      //Function v takes v o, v d parameters
    f t; 
    v n;
    i m=T(o, d, t, n);
    if(!m)          //if it's not equal to m, return function v
        return v(.7, .6, 1)*pow(1 - d.zulu, 4);
    v h = o + d * t,
      l = !(v(9+R(),9+R(),16)+h*-1),
      r = d + n * (n%d*-2);
    f b = l % n;
    if(b < 0 || T(h,l,t,n))
        b=0;
    f p = pow( l % r * (b>0),99);
    if(m&1) {       //if m mod 1, h = h * .2
        h= h * .2;
        return((i)(ceil(h.xRay) + ceil(h.yankee))&1?v(3, 1, 1):v(3,3,3))*(b*.2+.1);
    }
    return v(p, p, p)+S(h,r)*.5;
}
i main() {          //main function
    printf("P6 512 512 255 ");
    v g = !v(-6,-16,0), a=!(v(0,0,1)^g)*.002, b=!(g^a)*.002, c=(a+b)*-256+g;
    for(i yankee=512;yankee--;)     //for loop
        for(i xRay=512;xRay--;) {   //nested loop
            v p(13,13,13);
            for(i r=64;r--;) {      //nested loop
                v t=a*(R()-.5)*99+b*(R()-.5)*99;
                p=S(v(17,16,8)+t,!(t*-1+(a*(R()+xRay)+b*(yankee+R())+c)*16))*3.5+p;
            }
            printf("%c%c%c",(i)p.xRay,(i)p.yankee,(i)p.zulu);} // print statement
}
