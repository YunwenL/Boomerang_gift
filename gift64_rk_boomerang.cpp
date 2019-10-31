//boomerang search with SMT encoding of the DDT and BCT

#include<iostream>
#include<cstdlib>
#include<cmath>
#include<cstring>

using namespace std;

int main(int argc, char *argv[]){
  const int T1 = atoi(argv[1]);
  const int bound1 = atoi(argv[2]);
  const int T2 = atoi(argv[3]);
  const int bound2 = atoi(argv[4]);
  const int bound3 = atoi(argv[5]);
  //const int AS = atoi(argv[3]);
  cout << "(set-logic QF_ABV)" << endl;
  cout << "(set-info :smt-lib-version 2.5)" <<endl;
  cout << "(set-option :produce-models true)" <<endl;
  for(int i=0; i<(T1+T2+1); i++){      //declare variables
  for(int j=0; j<=15; j++){
		cout << "(declare-fun a"<<j<<"_"<<i<<" () (_ BitVec 4)) ";
		cout << "(declare-fun b"<<j<<"_"<<i<<" () (_ BitVec 4)) ";
	 cout << "(declare-fun pon"<<j<<"_"<<i<<" () (_ BitVec 1)) ";  //2^-2
	 cout << "(declare-fun ptw"<<j<<"_"<<i<<" () (_ BitVec 1)) ";  //2^-3
	 cout << "(declare-fun pth"<<j<<"_"<<i<<" () (_ BitVec 1)) ";  //2^-1.4
  }}

  for(int j=0; j<=15; j++){
  cout << "(declare-fun a"<<j<<"_"<<(T1+T2+1)<<" () (_ BitVec 4)) " ;
  cout << "(declare-fun pfo"<<j<<" () (_ BitVec 1)) ";  //2^-1
  cout << "(declare-fun pfi"<<j<<" () (_ BitVec 1)) ";  //2^-0.7  //these two variables are only for the middle switch
  cout << "(declare-fun psi"<<j<<" () (_ BitVec 1)) ";  //2^0 (entry 16 in BCT)
  }
  for(int i=0; i<(T1+T2+1); i++){    //key from key schdule
  cout <<"(declare-fun k0_"<<i<<" () (_ BitVec 16)) "<< endl;
  cout <<"(declare-fun k1_"<<i<<" () (_ BitVec 16)) "<< endl;
  }
  for(int i=0; i<=(T1+T2+1); i++){    //round keys
  for(int j=0; j<=15; j++){
		cout << "(declare-fun key"<<j<<"_"<<i<<" () (_ BitVec 4)) ";
  }}
  //weight for E1
  cout <<"(declare-fun weight1 () (_ BitVec 16))"<<endl;
  cout <<"(declare-fun weight2 () (_ BitVec 16))"<<endl;
  cout <<"(declare-fun weight3 () (_ BitVec 16))"<<endl;
  //weight for E2
  cout <<"(declare-fun weight4 () (_ BitVec 16))"<<endl;
  cout <<"(declare-fun weight5 () (_ BitVec 16))"<<endl;
  cout <<"(declare-fun weight6 () (_ BitVec 16))"<<endl;

  cout << endl;
  cout <<"(define-fun w_A ((x (_ BitVec 4))) (_ BitVec 16)  (bvor (bvand (bvlshr (concat (_ bv0 12) x) #x0003) #x0001) (bvor (bvand (bvlshr (concat (_ bv0 12) x) #x0002) #x0001) (bvor (bvand (concat (_ bv0 12) x) #x0001) (bvand (bvlshr (concat (_ bv0 12) x) #x0001) #x0001))))) ;test if an sbox(4-bit) is active" << endl;
  cout <<"(define-fun shuffle ((x3 (_ BitVec 4)) (x2 (_ BitVec 4)) (x1 (_ BitVec 4)) (x0 (_ BitVec 4))) (_ BitVec 4) (concat ((_ extract 3 3)x3) (concat ((_ extract 2 2)x2) (concat ((_ extract 1 1)x1) ((_ extract 0 0)x0)))))"<< endl;

//E1
  //----------------sbox-----------------//   gift
  for(int i=0; i<T1; i++){
  for(int j=0; j<=15; j++){
    cout <<"(assert (= pon"<<j<<"_"<<i<<" (bvor ";
    cout <<"(bvand (= a"<<j<<"_"<<i<<" #x2) (bvor (= b"<<j<<"_"<<i<<" #x5) (= b"<<j<<"_"<<i<<" #x6))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x4) (= b"<<j<<"_"<<i<<" #x5)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x5) (= b"<<j<<"_"<<i<<" #xf)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x6) (= b"<<j<<"_"<<i<<" #x2)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x7) (= b"<<j<<"_"<<i<<" #xb)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #x3) (bvor (= b"<<j<<"_"<<i<<" #x7) (bvor (= b"<<j<<"_"<<i<<" #xb) (= b"<<j<<"_"<<i<<" #xf))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #x1) (= b"<<j<<"_"<<i<<" #x6))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xc) (bvor (= b"<<j<<"_"<<i<<" #x2) (= b"<<j<<"_"<<i<<" #x4))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xd) (= b"<<j<<"_"<<i<<" #x4)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xe) (bvor (= b"<<j<<"_"<<i<<" #x1) (= b"<<j<<"_"<<i<<" #x4))) ";
    cout <<"(bvand (= a"<<j<<"_"<<i<<" #xf) (= b"<<j<<"_"<<i<<" #x4))) ";
    cout <<")))))))))))"<<endl;
  }}
  for(int i=0; i<T1; i++){
  for(int j=0; j<=15; j++){
    cout <<"(assert (= ptw"<<j<<"_"<<i<<" (bvor ";
    cout <<"(bvand (= a"<<j<<"_"<<i<<" #x1) (bvor (= b"<<j<<"_"<<i<<" #x5) (bvor (= b"<<j<<"_"<<i<<" #x6) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #xb) (bvor (= b"<<j<<"_"<<i<<" #xc) (= b"<<j<<"_"<<i<<" #xf))))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x2) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #xd) (= b"<<j<<"_"<<i<<" #xe))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x3) (bvor (= b"<<j<<"_"<<i<<" #x5) (bvor (= b"<<j<<"_"<<i<<" #x6) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #xb) (bvor (= b"<<j<<"_"<<i<<" #xc) (bvor (= b"<<j<<"_"<<i<<" #xd) (bvor (= b"<<j<<"_"<<i<<" #xe) (= b"<<j<<"_"<<i<<" #xf))))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x4) (bvor (= b"<<j<<"_"<<i<<" #x3) (bvor (= b"<<j<<"_"<<i<<" #x9) (= b"<<j<<"_"<<i<<" #xd)))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x5) (bvor (= b"<<j<<"_"<<i<<" #x2) (bvor (= b"<<j<<"_"<<i<<" #x5) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #xc) (bvor (= b"<<j<<"_"<<i<<" #xd) (= b"<<j<<"_"<<i<<" #xe))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x6) (bvor (= b"<<j<<"_"<<i<<" #x7) (bvor (= b"<<j<<"_"<<i<<" #xa) (= b"<<j<<"_"<<i<<" #xe)))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x7) (bvor (= b"<<j<<"_"<<i<<" #x2) (bvor (= b"<<j<<"_"<<i<<" #x5) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xa) (= b"<<j<<"_"<<i<<" #xc))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #x1) (bvor (= b"<<j<<"_"<<i<<" #x3) (bvor (= b"<<j<<"_"<<i<<" #x6) (bvor (= b"<<j<<"_"<<i<<" #x7) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #xc) (= b"<<j<<"_"<<i<<" #xd))))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #xd) (= b"<<j<<"_"<<i<<" #xe))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xb) (bvor (= b"<<j<<"_"<<i<<" #x1) (bvor (= b"<<j<<"_"<<i<<" #x3) (bvor (= b"<<j<<"_"<<i<<" #x6) (bvor (= b"<<j<<"_"<<i<<" #x7) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xc) (= b"<<j<<"_"<<i<<" #xe))))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xc) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #xc) (= b"<<j<<"_"<<i<<" #xe))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xd) (bvor (= b"<<j<<"_"<<i<<" #x1) (bvor (= b"<<j<<"_"<<i<<" #x2) (bvor (= b"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #xb) (bvor (= b"<<j<<"_"<<i<<" #xd) (= b"<<j<<"_"<<i<<" #xf))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xe) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xc) (= b"<<j<<"_"<<i<<" #xd))))) ";
    cout <<"(bvand (= a"<<j<<"_"<<i<<" #xf) (bvor (= b"<<j<<"_"<<i<<" #x1) (bvor (= b"<<j<<"_"<<i<<" #x2) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xb) (bvor (= b"<<j<<"_"<<i<<" #xe) (= b"<<j<<"_"<<i<<" #xf))))))) ";
    cout <<")))))))))))))))"<<endl;
  }}
  for(int i=0; i<T1; i++){
  for(int j=0; j<=15; j++){
    cout <<"(assert (= pth"<<j<<"_"<<i<<" (bvor ";
    cout <<"(bvand (= a"<<j<<"_"<<i<<" #x4) (= b"<<j<<"_"<<i<<" #x7)) ";
    cout <<"(bvand (= a"<<j<<"_"<<i<<" #x6) (= b"<<j<<"_"<<i<<" #x3)) ";
    cout <<")))"<<endl;
  }}

  for(int i=0; i<T1; i++){
  for(int j=0; j<=15; j++){
    cout <<"(assert (= (w_A a"<<j<<"_"<<i<<") (bvadd (concat (_ bv0 15) pon"<<j<<"_"<<i<<") (bvadd (concat (_ bv0 15) ptw"<<j<<"_"<<i<<") (concat (_ bv0 15) pth"<<j<<"_"<<i<<")))))"<<endl;
  }}

  for(int i=0; i<T1; i++){
  for(int j=0; j<=15; j++){
    cout <<"(assert (= (w_A a"<<j<<"_"<<i<<") (w_A b"<<j<<"_"<<i<<")))"<< endl;
  }}
  //----------------bit shuffle-----------------//
  for(int i=0; i<T1; i++){
    cout <<"(assert (= a15_"<<i+1<<" (bvxor key15_"<<i<<" (shuffle b12_"<<i<<" b15_"<<i<<" b14_"<<i<<" b13_"<<i<<"))))"<< endl;
    cout <<"(assert (= a14_"<<i+1<<" (bvxor key14_"<<i<<" (shuffle b8_"<<i<<" b11_"<<i<<" b10_"<<i<<" b9_"<<i<<"))))"<< endl;
    cout <<"(assert (= a13_"<<i+1<<" (bvxor key13_"<<i<<" (shuffle b4_"<<i<<" b7_"<<i<<" b6_"<<i<<" b5_"<<i<<"))))"<< endl;
    cout <<"(assert (= a12_"<<i+1<<" (bvxor key12_"<<i<<" (shuffle b0_"<<i<<" b3_"<<i<<" b2_"<<i<<" b1_"<<i<<"))))"<< endl;
    cout <<"(assert (= a11_"<<i+1<<" (bvxor key11_"<<i<<" (shuffle b13_"<<i<<" b12_"<<i<<" b15_"<<i<<" b14_"<<i<<"))))"<< endl;
    cout <<"(assert (= a10_"<<i+1<<" (bvxor key10_"<<i<<" (shuffle b9_"<<i<<" b8_"<<i<<" b11_"<<i<<" b10_"<<i<<"))))"<< endl;
    cout <<"(assert (= a9_"<<i+1<<" (bvxor key9_"<<i<<" (shuffle b5_"<<i<<" b4_"<<i<<" b7_"<<i<<" b6_"<<i<<"))))"<< endl;
    cout <<"(assert (= a8_"<<i+1<<" (bvxor key8_"<<i<<" (shuffle b1_"<<i<<" b0_"<<i<<" b3_"<<i<<" b2_"<<i<<"))))"<< endl;
    cout <<"(assert (= a7_"<<i+1<<" (bvxor key7_"<<i<<" (shuffle b14_"<<i<<" b13_"<<i<<" b12_"<<i<<" b15_"<<i<<"))))"<< endl;
    cout <<"(assert (= a6_"<<i+1<<" (bvxor key6_"<<i<<" (shuffle b10_"<<i<<" b9_"<<i<<" b8_"<<i<<" b11_"<<i<<"))))"<< endl;
    cout <<"(assert (= a5_"<<i+1<<" (bvxor key5_"<<i<<" (shuffle b6_"<<i<<" b5_"<<i<<" b4_"<<i<<" b7_"<<i<<"))))"<< endl;
    cout <<"(assert (= a4_"<<i+1<<" (bvxor key4_"<<i<<" (shuffle b2_"<<i<<" b1_"<<i<<" b0_"<<i<<" b3_"<<i<<"))))"<< endl;
    cout <<"(assert (= a3_"<<i+1<<" (bvxor key3_"<<i<<" (shuffle b15_"<<i<<" b14_"<<i<<" b13_"<<i<<" b12_"<<i<<"))))"<< endl;
    cout <<"(assert (= a2_"<<i+1<<" (bvxor key2_"<<i<<" (shuffle b11_"<<i<<" b10_"<<i<<" b9_"<<i<<" b8_"<<i<<"))))"<< endl;
    cout <<"(assert (= a1_"<<i+1<<" (bvxor key1_"<<i<<" (shuffle b7_"<<i<<" b6_"<<i<<" b5_"<<i<<" b4_"<<i<<"))))"<< endl;
    cout <<"(assert (= a0_"<<i+1<<" (bvxor key0_"<<i<<" (shuffle b3_"<<i<<" b2_"<<i<<" b1_"<<i<<" b0_"<<i<<"))))"<< endl;
  }

//E2
  //----------------sbox-----------------//   gift
  for(int i=(T1+1); i<(T1+T2+1); i++){
  for(int j=0; j<=15; j++){
    cout <<"(assert (= pon"<<j<<"_"<<i<<" (bvor ";
    cout <<"(bvand (= a"<<j<<"_"<<i<<" #x2) (bvor (= b"<<j<<"_"<<i<<" #x5) (= b"<<j<<"_"<<i<<" #x6))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x4) (= b"<<j<<"_"<<i<<" #x5)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x5) (= b"<<j<<"_"<<i<<" #xf)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x6) (= b"<<j<<"_"<<i<<" #x2)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x7) (= b"<<j<<"_"<<i<<" #xb)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #x3) (bvor (= b"<<j<<"_"<<i<<" #x7) (bvor (= b"<<j<<"_"<<i<<" #xb) (= b"<<j<<"_"<<i<<" #xf))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #x1) (= b"<<j<<"_"<<i<<" #x6))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xc) (bvor (= b"<<j<<"_"<<i<<" #x2) (= b"<<j<<"_"<<i<<" #x4))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xd) (= b"<<j<<"_"<<i<<" #x4)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xe) (bvor (= b"<<j<<"_"<<i<<" #x1) (= b"<<j<<"_"<<i<<" #x4))) ";
    cout <<"(bvand (= a"<<j<<"_"<<i<<" #xf) (= b"<<j<<"_"<<i<<" #x4))) ";
    cout <<")))))))))))"<<endl;
  }}
  for(int i=(T1+1); i<(T1+T2+1); i++){
  for(int j=0; j<=15; j++){
    cout <<"(assert (= ptw"<<j<<"_"<<i<<" (bvor ";
    cout <<"(bvand (= a"<<j<<"_"<<i<<" #x1) (bvor (= b"<<j<<"_"<<i<<" #x5) (bvor (= b"<<j<<"_"<<i<<" #x6) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #xb) (bvor (= b"<<j<<"_"<<i<<" #xc) (= b"<<j<<"_"<<i<<" #xf))))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x2) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #xd) (= b"<<j<<"_"<<i<<" #xe))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x3) (bvor (= b"<<j<<"_"<<i<<" #x5) (bvor (= b"<<j<<"_"<<i<<" #x6) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #xb) (bvor (= b"<<j<<"_"<<i<<" #xc) (bvor (= b"<<j<<"_"<<i<<" #xd) (bvor (= b"<<j<<"_"<<i<<" #xe) (= b"<<j<<"_"<<i<<" #xf))))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x4) (bvor (= b"<<j<<"_"<<i<<" #x3) (bvor (= b"<<j<<"_"<<i<<" #x9) (= b"<<j<<"_"<<i<<" #xd)))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x5) (bvor (= b"<<j<<"_"<<i<<" #x2) (bvor (= b"<<j<<"_"<<i<<" #x5) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #xc) (bvor (= b"<<j<<"_"<<i<<" #xd) (= b"<<j<<"_"<<i<<" #xe))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x6) (bvor (= b"<<j<<"_"<<i<<" #x7) (bvor (= b"<<j<<"_"<<i<<" #xa) (= b"<<j<<"_"<<i<<" #xe)))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x7) (bvor (= b"<<j<<"_"<<i<<" #x2) (bvor (= b"<<j<<"_"<<i<<" #x5) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xa) (= b"<<j<<"_"<<i<<" #xc))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #x1) (bvor (= b"<<j<<"_"<<i<<" #x3) (bvor (= b"<<j<<"_"<<i<<" #x6) (bvor (= b"<<j<<"_"<<i<<" #x7) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #xc) (= b"<<j<<"_"<<i<<" #xd))))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #xd) (= b"<<j<<"_"<<i<<" #xe))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xb) (bvor (= b"<<j<<"_"<<i<<" #x1) (bvor (= b"<<j<<"_"<<i<<" #x3) (bvor (= b"<<j<<"_"<<i<<" #x6) (bvor (= b"<<j<<"_"<<i<<" #x7) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xc) (= b"<<j<<"_"<<i<<" #xe))))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xc) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #xc) (= b"<<j<<"_"<<i<<" #xe))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xd) (bvor (= b"<<j<<"_"<<i<<" #x1) (bvor (= b"<<j<<"_"<<i<<" #x2) (bvor (= b"<<j<<"_"<<i<<" #xa) (bvor (= b"<<j<<"_"<<i<<" #xb) (bvor (= b"<<j<<"_"<<i<<" #xd) (= b"<<j<<"_"<<i<<" #xf))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<i<<" #xe) (bvor (= b"<<j<<"_"<<i<<" #x8) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xc) (= b"<<j<<"_"<<i<<" #xd))))) ";
    cout <<"(bvand (= a"<<j<<"_"<<i<<" #xf) (bvor (= b"<<j<<"_"<<i<<" #x1) (bvor (= b"<<j<<"_"<<i<<" #x2) (bvor (= b"<<j<<"_"<<i<<" #x9) (bvor (= b"<<j<<"_"<<i<<" #xb) (bvor (= b"<<j<<"_"<<i<<" #xe) (= b"<<j<<"_"<<i<<" #xf))))))) ";
    cout <<")))))))))))))))"<<endl;
  }}
  for(int i=(T1+1); i<(T1+T2+1); i++){
  for(int j=0; j<=15; j++){
    cout <<"(assert (= pth"<<j<<"_"<<i<<" (bvor ";
    cout <<"(bvand (= a"<<j<<"_"<<i<<" #x4) (= b"<<j<<"_"<<i<<" #x7)) ";
    cout <<"(bvand (= a"<<j<<"_"<<i<<" #x6) (= b"<<j<<"_"<<i<<" #x3)) ";
    cout <<")))"<<endl;
  }}

  for(int i=(T1+1); i<(T1+T2+1); i++){
  for(int j=0; j<=15; j++){
    cout <<"(assert (= (w_A a"<<j<<"_"<<i<<") (bvadd (concat (_ bv0 15) pon"<<j<<"_"<<i<<") (bvadd (concat (_ bv0 15) ptw"<<j<<"_"<<i<<") (concat (_ bv0 15) pth"<<j<<"_"<<i<<")))))"<<endl;
  }}

  for(int i=(T1+1); i<(T1+T2+1); i++){
  for(int j=0; j<=15; j++){
    cout <<"(assert (= (w_A a"<<j<<"_"<<i<<") (w_A b"<<j<<"_"<<i<<")))"<< endl;
  }}
  //----------------bit shuffle-----------------//
  for(int i=(T1+1); i<(T1+T2+1); i++){
    cout <<"(assert (= a15_"<<i+1<<" (bvxor key15_"<<i<<" (shuffle b12_"<<i<<" b15_"<<i<<" b14_"<<i<<" b13_"<<i<<"))))"<< endl;
    cout <<"(assert (= a14_"<<i+1<<" (bvxor key14_"<<i<<" (shuffle b8_"<<i<<" b11_"<<i<<" b10_"<<i<<" b9_"<<i<<"))))"<< endl;
    cout <<"(assert (= a13_"<<i+1<<" (bvxor key13_"<<i<<" (shuffle b4_"<<i<<" b7_"<<i<<" b6_"<<i<<" b5_"<<i<<"))))"<< endl;
    cout <<"(assert (= a12_"<<i+1<<" (bvxor key12_"<<i<<" (shuffle b0_"<<i<<" b3_"<<i<<" b2_"<<i<<" b1_"<<i<<"))))"<< endl;
    cout <<"(assert (= a11_"<<i+1<<" (bvxor key11_"<<i<<" (shuffle b13_"<<i<<" b12_"<<i<<" b15_"<<i<<" b14_"<<i<<"))))"<< endl;
    cout <<"(assert (= a10_"<<i+1<<" (bvxor key10_"<<i<<" (shuffle b9_"<<i<<" b8_"<<i<<" b11_"<<i<<" b10_"<<i<<"))))"<< endl;
    cout <<"(assert (= a9_"<<i+1<<" (bvxor key9_"<<i<<" (shuffle b5_"<<i<<" b4_"<<i<<" b7_"<<i<<" b6_"<<i<<"))))"<< endl;
    cout <<"(assert (= a8_"<<i+1<<" (bvxor key8_"<<i<<" (shuffle b1_"<<i<<" b0_"<<i<<" b3_"<<i<<" b2_"<<i<<"))))"<< endl;
    cout <<"(assert (= a7_"<<i+1<<" (bvxor key7_"<<i<<" (shuffle b14_"<<i<<" b13_"<<i<<" b12_"<<i<<" b15_"<<i<<"))))"<< endl;
    cout <<"(assert (= a6_"<<i+1<<" (bvxor key6_"<<i<<" (shuffle b10_"<<i<<" b9_"<<i<<" b8_"<<i<<" b11_"<<i<<"))))"<< endl;
    cout <<"(assert (= a5_"<<i+1<<" (bvxor key5_"<<i<<" (shuffle b6_"<<i<<" b5_"<<i<<" b4_"<<i<<" b7_"<<i<<"))))"<< endl;
    cout <<"(assert (= a4_"<<i+1<<" (bvxor key4_"<<i<<" (shuffle b2_"<<i<<" b1_"<<i<<" b0_"<<i<<" b3_"<<i<<"))))"<< endl;
    cout <<"(assert (= a3_"<<i+1<<" (bvxor key3_"<<i<<" (shuffle b15_"<<i<<" b14_"<<i<<" b13_"<<i<<" b12_"<<i<<"))))"<< endl;
    cout <<"(assert (= a2_"<<i+1<<" (bvxor key2_"<<i<<" (shuffle b11_"<<i<<" b10_"<<i<<" b9_"<<i<<" b8_"<<i<<"))))"<< endl;
    cout <<"(assert (= a1_"<<i+1<<" (bvxor key1_"<<i<<" (shuffle b7_"<<i<<" b6_"<<i<<" b5_"<<i<<" b4_"<<i<<"))))"<< endl;
    cout <<"(assert (= a0_"<<i+1<<" (bvxor key0_"<<i<<" (shuffle b3_"<<i<<" b2_"<<i<<" b1_"<<i<<" b0_"<<i<<"))))"<< endl;
  }

//middle switch, with BCT table
  for(int j=0; j<=15; j++){  //BCT = 4
    cout <<"(assert (= pon"<<j<<"_"<<T1<<" (bvor ";
    cout <<"(bvand (= a"<<j<<"_"<<T1<<" #x2) (bvor (= b"<<j<<"_"<<T1<<" #x2) (bvor (= b"<<j<<"_"<<T1<<" #x3) (bvor (= b"<<j<<"_"<<T1<<" #x6) (= b"<<j<<"_"<<T1<<" #x7))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x4) (bvor (= b"<<j<<"_"<<T1<<" #x1) (bvor (= b"<<j<<"_"<<T1<<" #x2) (= b"<<j<<"_"<<T1<<" #x4)))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x5) (bvor (= b"<<j<<"_"<<T1<<" #x4) (bvor (= b"<<j<<"_"<<T1<<" #xb) (= b"<<j<<"_"<<T1<<" #xf)))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x6) (bvor (= b"<<j<<"_"<<T1<<" #x1) (bvor (= b"<<j<<"_"<<T1<<" #x4) (= b"<<j<<"_"<<T1<<" #x6)))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x7) (bvor (= b"<<j<<"_"<<T1<<" #x4) (bvor (= b"<<j<<"_"<<T1<<" #xb) (= b"<<j<<"_"<<T1<<" #xf)))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xa) (bvor (= b"<<j<<"_"<<T1<<" #x2) (bvor (= b"<<j<<"_"<<T1<<" #x3) (bvor (= b"<<j<<"_"<<T1<<" #x6) (= b"<<j<<"_"<<T1<<" #x7))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xc) (bvor (= b"<<j<<"_"<<T1<<" #x1) (bvor (= b"<<j<<"_"<<T1<<" #x2) (bvor (= b"<<j<<"_"<<T1<<" #x4) (= b"<<j<<"_"<<T1<<" #x7))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xd) (= b"<<j<<"_"<<T1<<" #x4)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xe) (bvor (= b"<<j<<"_"<<T1<<" #x1) (bvor (= b"<<j<<"_"<<T1<<" #x3) (bvor (= b"<<j<<"_"<<T1<<" #x4) (= b"<<j<<"_"<<T1<<" #x6))))) ";
    cout <<"(bvand (= a"<<j<<"_"<<T1<<" #xf) (= b"<<j<<"_"<<T1<<" #x4))) ";
    cout <<"))))))))))"<<endl;
  }
  
  for(int j=0; j<=15; j++){  //BCT = 2
    cout <<"(assert (= ptw"<<j<<"_"<<T1<<" (bvor ";
    cout <<"(bvand (= a"<<j<<"_"<<T1<<" #x1) (bvor (= b"<<j<<"_"<<T1<<" #x5) (bvor (= b"<<j<<"_"<<T1<<" #x6) (bvor (= b"<<j<<"_"<<T1<<" #x8) (bvor (= b"<<j<<"_"<<T1<<" #x9) (bvor (= b"<<j<<"_"<<T1<<" #xa) (bvor (= b"<<j<<"_"<<T1<<" #xb) (bvor (= b"<<j<<"_"<<T1<<" #xc) (= b"<<j<<"_"<<T1<<" #xf))))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x2) (bvor (= b"<<j<<"_"<<T1<<" #x9) (bvor (= b"<<j<<"_"<<T1<<" #xa) (bvor (= b"<<j<<"_"<<T1<<" #xd) (= b"<<j<<"_"<<T1<<" #xe))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x3) (bvor (= b"<<j<<"_"<<T1<<" #x5) (bvor (= b"<<j<<"_"<<T1<<" #x6) (bvor (= b"<<j<<"_"<<T1<<" #x8) (bvor (= b"<<j<<"_"<<T1<<" #xb) (bvor (= b"<<j<<"_"<<T1<<" #xc) (bvor (= b"<<j<<"_"<<T1<<" #xd) (bvor (= b"<<j<<"_"<<T1<<" #xe) (= b"<<j<<"_"<<T1<<" #xf))))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x4) (bvor (= b"<<j<<"_"<<T1<<" #x9) (= b"<<j<<"_"<<T1<<" #xd))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x5) (bvor (= b"<<j<<"_"<<T1<<" #x2) (bvor (= b"<<j<<"_"<<T1<<" #x5) (bvor (= b"<<j<<"_"<<T1<<" #x8) (bvor (= b"<<j<<"_"<<T1<<" #xc) (bvor (= b"<<j<<"_"<<T1<<" #xd) (= b"<<j<<"_"<<T1<<" #xe))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x6) (bvor (= b"<<j<<"_"<<T1<<" #xa) (= b"<<j<<"_"<<T1<<" #xe))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x7) (bvor (= b"<<j<<"_"<<T1<<" #x2) (bvor (= b"<<j<<"_"<<T1<<" #x5) (bvor (= b"<<j<<"_"<<T1<<" #x8) (bvor (= b"<<j<<"_"<<T1<<" #x9) (bvor (= b"<<j<<"_"<<T1<<" #xa) (= b"<<j<<"_"<<T1<<" #xc))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x9) (bvor (= b"<<j<<"_"<<T1<<" #x1) (bvor (= b"<<j<<"_"<<T1<<" #x3) (bvor (= b"<<j<<"_"<<T1<<" #x6) (bvor (= b"<<j<<"_"<<T1<<" #x7) (bvor (= b"<<j<<"_"<<T1<<" #x8) (bvor (= b"<<j<<"_"<<T1<<" #xa) (bvor (= b"<<j<<"_"<<T1<<" #xc) (= b"<<j<<"_"<<T1<<" #xd))))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xa) (bvor (= b"<<j<<"_"<<T1<<" #x9) (bvor (= b"<<j<<"_"<<T1<<" #xa) (bvor (= b"<<j<<"_"<<T1<<" #xd) (= b"<<j<<"_"<<T1<<" #xe))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xb) (bvor (= b"<<j<<"_"<<T1<<" #x1) (bvor (= b"<<j<<"_"<<T1<<" #x3) (bvor (= b"<<j<<"_"<<T1<<" #x6) (bvor (= b"<<j<<"_"<<T1<<" #x7) (bvor (= b"<<j<<"_"<<T1<<" #x8) (bvor (= b"<<j<<"_"<<T1<<" #x9) (bvor (= b"<<j<<"_"<<T1<<" #xc) (= b"<<j<<"_"<<T1<<" #xe))))))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xc) (bvor (= b"<<j<<"_"<<T1<<" #x8) (bvor (= b"<<j<<"_"<<T1<<" #xa) (bvor (= b"<<j<<"_"<<T1<<" #xc) (= b"<<j<<"_"<<T1<<" #xe))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xd) (bvor (= b"<<j<<"_"<<T1<<" #x1) (bvor (= b"<<j<<"_"<<T1<<" #x2) (bvor (= b"<<j<<"_"<<T1<<" #xa) (= b"<<j<<"_"<<T1<<" #xd) )))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xe) (bvor (= b"<<j<<"_"<<T1<<" #x8) (bvor (= b"<<j<<"_"<<T1<<" #x9) (bvor (= b"<<j<<"_"<<T1<<" #xc) (= b"<<j<<"_"<<T1<<" #xd))))) ";
    cout <<"(bvand (= a"<<j<<"_"<<T1<<" #xf) (bvor (= b"<<j<<"_"<<T1<<" #x1) (bvor (= b"<<j<<"_"<<T1<<" #x2) (bvor (= b"<<j<<"_"<<T1<<" #x9)(= b"<<j<<"_"<<T1<<" #xe) )))) ";
    cout <<")))))))))))))))"<<endl;
  }
  
  for(int j=0; j<=15; j++){
    cout <<"(assert (= pth"<<j<<"_"<<T1<<" (bvor ";
    cout <<"(bvand (= a"<<j<<"_"<<T1<<" #x4) (= b"<<j<<"_"<<T1<<" #x7)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x6) (= b"<<j<<"_"<<T1<<" #x3)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xd) (bvor (= b"<<j<<"_"<<T1<<" #xb) (= b"<<j<<"_"<<T1<<" #xf))) ";
    cout <<"(bvand (= a"<<j<<"_"<<T1<<" #xf) (bvor (= b"<<j<<"_"<<T1<<" #xb) (= b"<<j<<"_"<<T1<<" #xf))) ";
    cout <<")))))"<<endl;
  }

  for(int j=0; j<=15; j++){
    cout <<"(assert (= pfo"<<j<<" (bvor ";
    cout <<"(bvand (= a"<<j<<"_"<<T1<<" #x2) (= b"<<j<<"_"<<T1<<" #x5)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x4) (bvor (= b"<<j<<"_"<<T1<<" #x5) (= b"<<j<<"_"<<T1<<" #x6))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x6) (bvor (= b"<<j<<"_"<<T1<<" #x2) (= b"<<j<<"_"<<T1<<" #x5))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x8) (bvor (= b"<<j<<"_"<<T1<<" #x3) (bvor (= b"<<j<<"_"<<T1<<" #x7) (bvor (= b"<<j<<"_"<<T1<<" #xb) (= b"<<j<<"_"<<T1<<" #xf))))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xa) (= b"<<j<<"_"<<T1<<" #x1)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xc) (= b"<<j<<"_"<<T1<<" #x3)) ";
    cout <<"(bvand (= a"<<j<<"_"<<T1<<" #xe) (= b"<<j<<"_"<<T1<<" #x7)) ";
    cout <<"))))))))"<<endl;
  }

  for(int j=0; j<=15; j++){
    cout <<"(assert (= pfi"<<j<<" (bvor ";
    cout <<"(bvand (= a"<<j<<"_"<<T1<<" #x4) (= b"<<j<<"_"<<T1<<" #x3)) ";
    cout <<"(bvand (= a"<<j<<"_"<<T1<<" #x6) (= b"<<j<<"_"<<T1<<" #x7)) ";
    cout <<")))"<<endl;
  }

  for(int j=0; j<=15; j++){
    cout <<"(assert (= psi"<<j<<" (bvor ";
    cout <<"(= a"<<j<<"_"<<T1<<" #x0)";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x1) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x2) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x3) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x4) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x5) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x6) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x7) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x8) (bvor (= b"<<j<<"_"<<T1<<" #x0) (= b"<<j<<"_"<<T1<<" #x3))) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #x9) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xa) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xb) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xc) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xd) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvor (bvand (= a"<<j<<"_"<<T1<<" #xe) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<"(bvand (= a"<<j<<"_"<<T1<<" #xf) (= b"<<j<<"_"<<T1<<" #x0)) ";
    cout <<")))))))))))))))))"<<endl;
  }


  
  for(int j=0; j<=15; j++){
    cout <<"(assert (= (_ bv1 16) (bvadd (concat (_ bv0 15) pon"<<j<<"_"<<T1<<") (bvadd (concat (_ bv0 15) ptw"<<j<<"_"<<T1<<") (bvadd (concat (_ bv0 15) pth"<<j<<"_"<<T1<<") (bvadd (concat (_ bv0 15) pfo"<<j<<") (bvadd (concat (_ bv0 15) pfi"<<j<<") (concat (_ bv0 15) psi"<<j<<")))))))) "<<endl;
  }

  //----------------bit shuffle-----------------//
    cout <<"(assert (= a15_"<<(T1+1)<<" (bvxor key15_"<<T1<<" (shuffle b12_"<<T1<<" b15_"<<T1<<" b14_"<<T1<<" b13_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a14_"<<(T1+1)<<" (bvxor key14_"<<T1<<" (shuffle b8_"<<T1<<" b11_"<<T1<<" b10_"<<T1<<" b9_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a13_"<<(T1+1)<<" (bvxor key13_"<<T1<<" (shuffle b4_"<<T1<<" b7_"<<T1<<" b6_"<<T1<<" b5_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a12_"<<(T1+1)<<" (bvxor key12_"<<T1<<" (shuffle b0_"<<T1<<" b3_"<<T1<<" b2_"<<T1<<" b1_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a11_"<<(T1+1)<<" (bvxor key11_"<<T1<<" (shuffle b13_"<<T1<<" b12_"<<T1<<" b15_"<<T1<<" b14_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a10_"<<(T1+1)<<" (bvxor key10_"<<T1<<" (shuffle b9_"<<T1<<" b8_"<<T1<<" b11_"<<T1<<" b10_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a9_"<<(T1+1)<<" (bvxor key9_"<<T1<<" (shuffle b5_"<<T1<<" b4_"<<T1<<" b7_"<<T1<<" b6_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a8_"<<(T1+1)<<" (bvxor key8_"<<T1<<" (shuffle b1_"<<T1<<" b0_"<<T1<<" b3_"<<T1<<" b2_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a7_"<<(T1+1)<<" (bvxor key7_"<<T1<<" (shuffle b14_"<<T1<<" b13_"<<T1<<" b12_"<<T1<<" b15_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a6_"<<(T1+1)<<" (bvxor key6_"<<T1<<" (shuffle b10_"<<T1<<" b9_"<<T1<<" b8_"<<T1<<" b11_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a5_"<<(T1+1)<<" (bvxor key5_"<<T1<<" (shuffle b6_"<<T1<<" b5_"<<T1<<" b4_"<<T1<<" b7_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a4_"<<(T1+1)<<" (bvxor key4_"<<T1<<" (shuffle b2_"<<T1<<" b1_"<<T1<<" b0_"<<T1<<" b3_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a3_"<<(T1+1)<<" (bvxor key3_"<<T1<<" (shuffle b15_"<<T1<<" b14_"<<T1<<" b13_"<<T1<<" b12_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a2_"<<(T1+1)<<" (bvxor key2_"<<T1<<" (shuffle b11_"<<T1<<" b10_"<<T1<<" b9_"<<T1<<" b8_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a1_"<<(T1+1)<<" (bvxor key1_"<<T1<<" (shuffle b7_"<<T1<<" b6_"<<T1<<" b5_"<<T1<<" b4_"<<T1<<"))))"<< endl;
    cout <<"(assert (= a0_"<<(T1+1)<<" (bvxor key0_"<<T1<<" (shuffle b3_"<<T1<<" b2_"<<T1<<" b1_"<<T1<<" b0_"<<T1<<"))))"<< endl;



  //----------------key update-----------------//
  for(int i=0; i<T1-4; i++){
    cout <<"(assert (= k0_"<<i+4<<" ((_ rotate_right 12) k0_"<<i<<")))"<< endl;
    cout <<"(assert (= k1_"<<i+4<<" ((_ rotate_right 2) k1_"<<i<<")))"<< endl;
  }
  for(int i=0; i<T1; i++){
  for(int j=0; j<=15; j++){
    cout << "(assert (= key"<<j<<"_"<<i<<" (concat #b00 (concat ((_ extract "<<j<<" "<<j<<") k1_"<<i<<") ((_ extract "<<j<<" "<<j<<") k0_"<<i<<") ))))" << endl;
  }}

  for(int i=T1; i<(T1+T2+1-4); i++){
    cout <<"(assert (= k0_"<<i+4<<" ((_ rotate_right 12) k0_"<<i<<")))"<< endl;
    cout <<"(assert (= k1_"<<i+4<<" ((_ rotate_right 2) k1_"<<i<<")))"<< endl;
  }
  for(int i=T1; i<(T1+T2+1); i++){
  for(int j=0; j<=15; j++){
    cout << "(assert (= key"<<j<<"_"<<i<<" (concat #b00 (concat ((_ extract "<<j<<" "<<j<<") k1_"<<i<<") ((_ extract "<<j<<" "<<j<<") k0_"<<i<<") ))))" << endl;
  }}
  //----------------bounds-----------------//

  cout << "(assert (= weight1 ";
  for(int i=0; i<T1; i++){
  for(int j=0; j<=15; j++){
    if((i+1==T1) && (j==15)) cout << "(concat (_ bv0 15) pon15_"<<T1-1<<")";
    else cout << "(bvadd (concat (_ bv0 15) pon"<<j<<"_"<<i<<") ";
  }}
  for(int i=0; i<T1; i++){
  for(int j=0; j<=15; j++){
    cout <<")";
  }}
  cout << ")" <<endl;
  cout << "(assert (= weight2 ";
  for(int i=0; i<T1; i++){
  for(int j=0; j<=15; j++){
    if((i+1==T1) && (j==15)) cout << "(concat (_ bv0 15) ptw15_"<<T1-1<<")";
    else cout << "(bvadd (concat (_ bv0 15) ptw"<<j<<"_"<<i<<") ";
  }}
  for(int i=0; i<T1; i++){
  for(int j=0; j<=15; j++){
    cout <<")";
  }}
  cout << ")" <<endl;
  cout << "(assert (= weight3 ";
  for(int i=0; i<T1; i++){
  for(int j=0; j<=15; j++){
    if((i+1==T1) && (j==15)) cout << "(concat (_ bv0 15) pth15_"<<T1-1<<")";
    else cout << "(bvadd (concat (_ bv0 15) pth"<<j<<"_"<<i<<") ";
  }}
  for(int i=0; i<T1; i++){
  for(int j=0; j<=15; j++){
    cout <<")";
  }}
  cout << ")" <<endl;
//total weight 10*weight1 + 15*weight2 + 7*weight3
  cout <<"(assert (= (_ bv"<<bound1<<" 16) (bvadd (bvmul #x000a weight1) (bvadd (bvmul #x000f weight2) (bvmul #x0007 weight3)))))"<<endl;


  cout << "(assert (= weight4 ";
  for(int i=T1+1; i<(T1+T2+1); i++){
  for(int j=0; j<=15; j++){
    if((i+1==(T1+T2+1)) && (j==15)) cout << "(concat (_ bv0 15) pon15_"<<T1+T2<<")";
    else cout << "(bvadd (concat (_ bv0 15) pon"<<j<<"_"<<i<<") ";
  }}
  for(int i=T1+1; i<(T1+T2+1); i++){
  for(int j=0; j<=15; j++){
    cout <<")";
  }}
  cout << ")" <<endl;
  cout << "(assert (= weight5 ";
  for(int i=T1+1; i<(T1+T2+1); i++){
  for(int j=0; j<=15; j++){
    if((i+1==(T1+T2+1)) && (j==15)) cout << "(concat (_ bv0 15) ptw15_"<<T1+T2<<")";
    else cout << "(bvadd (concat (_ bv0 15) ptw"<<j<<"_"<<i<<") ";
  }}
  for(int i=T1+1; i<(T1+T2+1); i++){
  for(int j=0; j<=15; j++){
    cout <<")";
  }}
  cout << ")" <<endl;
  cout << "(assert (= weight6 ";
  for(int i=T1+1; i<(T1+T2+1); i++){
  for(int j=0; j<=15; j++){
    if((i+1==(T1+T2+1)) && (j==15)) cout << "(concat (_ bv0 15) pth15_"<<T1+T2<<")";
    else cout << "(bvadd (concat (_ bv0 15) pth"<<j<<"_"<<i<<") ";
  }}
  for(int i=T1+1; i<(T1+T2+1); i++){
  for(int j=0; j<=15; j++){
    cout <<")";
  }}
  cout << ")" <<endl;
//total weight 10*weight4 + 15*weight5 + 7*weight6
  cout <<"(assert (= (_ bv"<<bound2<<" 16) (bvadd (bvmul #x000a weight4) (bvadd (bvmul #x000f weight5) (bvmul #x0007 weight6)))))"<<endl;

//this is weight in middle switch
//0.7 * fi + 1 * fo + 1.4 * th + 2 * tw + 3 * on
  cout <<"(assert (bvule (_ bv"<<bound3<<" 16) ";   //bound3 > 1
  cout <<"(bvadd (bvmul #x0014 "; 
  for(int j=0; j<=15; j++){
  if(j<15) {cout <<"(bvadd (concat (_ bv0 15) pon"<<j<<"_"<<T1<<") ";}
  else {cout <<"(concat (_ bv0 15) pon"<<j<<"_"<<T1<<") ";}
  }
  cout <<")))))))))))))))) (bvadd (bvmul #x001e ";
  for(int j=0; j<=15; j++){
  if(j<15) {cout <<"(bvadd (concat (_ bv0 15) ptw"<<j<<"_"<<T1<<") ";}
  else {cout <<"(concat (_ bv0 15) ptw"<<j<<"_"<<T1<<") ";}
  }
  cout <<")))))))))))))))) (bvadd (bvmul #x000e ";
  for(int j=0; j<=15; j++){
  if(j<15) {cout <<"(bvadd (concat (_ bv0 15) pth"<<j<<"_"<<T1<<") ";}
  else {cout <<"(concat (_ bv0 15) pth"<<j<<"_"<<T1<<") ";}
  }
  cout <<")))))))))))))))) (bvadd (bvmul #x000a ";
  for(int j=0; j<=15; j++){
  if(j<15) {cout <<"(bvadd (concat (_ bv0 15) pfo"<<j<<") ";}
  else {cout <<"(concat (_ bv0 15) pfo"<<j<<") ";}
  }
  cout <<")))))))))))))))) (bvmul #x0007 ";
  for(int j=0; j<=15; j++){
  if(j<15) {cout <<"(bvadd (concat (_ bv0 15) pfi"<<j<<") ";}
  else {cout <<"(concat (_ bv0 15) pfi"<<j<<") ";}
  }
  cout <<"))))))))))))))))";
  cout <<"))))))"<<endl; 

  cout <<"(check-sat)"<< endl;
  for(int i=0; i<(T1+T2+1); i++){
    for(int j=0; j<=15; j++){cout << "(get-value (a"<<j<<"_"<<i<<"))" << "  ";}
    for(int j=0; j<=15; j++){cout << "(get-value (b"<<j<<"_"<<i<<"))" << "  ";}
    for(int j=0; j<=15; j++){cout << "(get-value (pon"<<j<<"_"<<i<<"))" << "  ";}
    for(int j=0; j<=15; j++){cout << "(get-value (ptw"<<j<<"_"<<i<<"))" << "  ";}
    for(int j=0; j<=15; j++){cout << "(get-value (pth"<<j<<"_"<<i<<"))" << "  ";}
    if(i==T1){ 
      for(int j=0; j<=15; j++){
        cout << "(get-value (pfo"<<j<<"))" << "  ";
        cout << "(get-value (pfi"<<j<<"))" << "  ";
        cout << "(get-value (psi"<<j<<"))" << "  ";
      }
    }
    cout <<"(get-value (k0_"<<i<<"))"<< endl;
    cout <<"(get-value (k1_"<<i<<"))"<< endl;
  }
  for(int j=0; j<=15; j++){cout << "(get-value (a"<<j<<"_"<<T1+T2+1<<"))" << "  ";}
  cout << "(get-value (weight1))" << endl;
  cout << "(get-value (weight2))" << endl;
  cout << "(get-value (weight3))" << endl;
  cout << "(get-value (weight4))" << endl;
  cout << "(get-value (weight5))" << endl;
  cout << "(get-value (weight6))" << endl;

  cout <<"(exit)"<<endl;
return 0;
}
