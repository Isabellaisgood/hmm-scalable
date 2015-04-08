/*
 
 Copyright (c) 2012-2014, Michael (Mikhail) Yudelson
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * Neither the name of the Michael (Mikhail) Yudelson nor the
 names of other contributors may be used to endorse or promote products
 derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 */
#include <iostream>
#include "FitBitSlicedAB.h"

FitBitSlicedAB::FitBitSlicedAB(NPAR a_nS, NPAR a_nO, NCAT a_nK, NCAT a_nG, NPAR a_nZ, NUMBER a_tol) {
    this->nS = a_nS;
    this->nO = a_nO;
    this->nG = a_nG;
    this->nK = a_nK;
    this->nZ = a_nZ;
    this->tol = a_tol;
    this->pi = NULL;
    this->A = NULL;
    this->B = NULL;
    this->PIm1 = NULL;
    this->Am1 = NULL;
    this->Bm1 = NULL;
    this->PIm2 = NULL;
    this->Am2 = NULL;
    this->Bm2 = NULL;
    this->gradPI = NULL;
    this->gradA = NULL;
    this->gradB = NULL;
    this->gradPIm1 = NULL;
    this->gradAm1 = NULL;
    this->gradBm1 = NULL;
    this->PIcopy = NULL;
    this->Acopy = NULL;
    this->Bcopy = NULL;
    this->dirPI = NULL;
    this->dirA = NULL;
    this->dirB = NULL;
    this->dirPIm1 = NULL;
    this->dirAm1 = NULL;
    this->dirBm1 = NULL;
    this->xndat = 0;
    this->x_data = 0;
    this->projecttosimplex = 1;
    this->Cslice = 0;
}

FitBitSlicedAB::FitBitSlicedAB(NPAR a_nS, NPAR a_nO, NCAT a_nK, NCAT a_nG, NPAR a_nZ, NUMBER a_tol, NPAR a_projecttosimplex) {
    this->nS = a_nS;
    this->nO = a_nO;
    this->nG = a_nG;
    this->nK = a_nK;
    this->nZ = a_nZ;
    this->tol = a_tol;
    this->pi = NULL;
    this->A = NULL;
    this->B = NULL;
    this->PIm1 = NULL;
    this->Am1 = NULL;
    this->Bm1 = NULL;
    this->PIm2 = NULL;
    this->Am2 = NULL;
    this->Bm2 = NULL;
    this->gradPI = NULL;
    this->gradA = NULL;
    this->gradB = NULL;
    this->gradPIm1 = NULL;
    this->gradAm1 = NULL;
    this->gradBm1 = NULL;
    this->PIcopy = NULL;
    this->Acopy = NULL;
    this->Bcopy = NULL;
    this->dirPI = NULL;
    this->dirA = NULL;
    this->dirB = NULL;
    this->dirPIm1 = NULL;
    this->dirAm1 = NULL;
    this->dirBm1 = NULL;
    this->xndat = 0;
    this->x_data = 0;
    this->projecttosimplex = a_projecttosimplex;
    this->Cslice = 0;
}

FitBitSlicedAB::~FitBitSlicedAB() {
//    if(this->pi != NULL) free(this->PI); // these are usually linked
//    if(this->A != NULL) free2D<NUMBER>(this->A, this->nS); // these are usually linked
//    if(this->B != NULL) free2D<NUMBER>(this->B, this->nS); // these are usually linked
    if(this->PIm1 != NULL) free(this->PIm1);
    if(this->Am1 != NULL) free3D<NUMBER>(this->Am1, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->Bm1 != NULL) free3D<NUMBER>(this->Bm1, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->PIm2 != NULL) free(this->PIm2);
    if(this->Am2 != NULL) free3D<NUMBER>(this->Am2, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->Bm2 != NULL) free3D<NUMBER>(this->Bm2, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->gradPI != NULL) free(this->gradPI);
    if(this->gradA != NULL) free3D<NUMBER>(this->gradA, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->gradB != NULL) free3D<NUMBER>(this->gradB, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->gradPIm1 != NULL) free(this->gradPIm1);
    if(this->gradAm1 != NULL) free3D<NUMBER>(this->gradAm1, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->gradBm1 != NULL) free3D<NUMBER>(this->gradBm1, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->PIcopy != NULL) free(this->PIcopy);
    if(this->Acopy != NULL) free3D<NUMBER>(this->Acopy, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->Bcopy != NULL) free3D<NUMBER>(this->Bcopy, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->dirPI != NULL) free(this->dirPI);
    if(this->dirA != NULL) free3D<NUMBER>(this->dirA, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->dirB != NULL) free3D<NUMBER>(this->dirB, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->dirPIm1 != NULL) free(this->dirPIm1);
    if(this->dirAm1 != NULL) free3D<NUMBER>(this->dirAm1, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->dirBm1 != NULL) free3D<NUMBER>(this->dirBm1, (NDAT)this->nZ, (NDAT)this->nS);
}

void FitBitSlicedAB::init(NUMBER* &a_PI, NUMBER*** &a_A, NUMBER*** &a_B) {
    if(this->pi != NULL) {
        if(a_PI == NULL)
            a_PI = init1D<NUMBER>((NDAT)this->nS); // init1DNumber(this->nS);
        else
            toZero1D<NUMBER>(a_PI, (NDAT)this->nS);
    }
    if(this->A  != NULL) {
        if(a_A == NULL)
            a_A  = init3D<NUMBER>((NDAT)this->nZ, (NDAT)this->nS, (NDAT)this->nS);
        else
            toZero3D<NUMBER>(a_A, (NDAT)this->nZ, (NDAT)this->nS, (NDAT)this->nS);
    }
    if(this->B  != NULL) {
        if(a_B == NULL)
            a_B  = init3D<NUMBER>((NDAT)this->nZ, (NDAT)this->nS, (NDAT)this->nO);
        else
            toZero3D<NUMBER>(a_B, (NDAT)this->nZ, (NDAT)this->nS, (NDAT)this->nO);
    }
}

void FitBitSlicedAB::link(NUMBER *a_PI, NUMBER ***a_A, NUMBER ***a_B, NCAT a_xndat, struct data** a_x_data) {
    this->pi = a_PI;
    this->A  = a_A;
    this->B  = a_B;
    this->xndat = a_xndat;
    this->x_data = a_x_data;
}

void FitBitSlicedAB::toZero(NUMBER *a_PI, NUMBER ***a_A, NUMBER ***a_B) {
    if(this->pi != NULL && a_PI != NULL) toZero1D<NUMBER>(a_PI, (NDAT)this->nS);
    if(this->A  != NULL && a_A  != NULL) toZero3D<NUMBER>(a_A,  (NDAT)this->nZ, (NDAT)this->nS, (NDAT)this->nS);
    if(this->B  != NULL && a_B  != NULL) toZero3D<NUMBER>(a_B,  (NDAT)this->nZ, (NDAT)this->nS, (NDAT)this->nO);
}

void FitBitSlicedAB::copy(NUMBER* &soursePI, NUMBER*** &sourseA, NUMBER*** &sourseB, NUMBER* &targetPI, NUMBER*** &targetA, NUMBER*** &targetB){
    if(this->pi != NULL) cpy1D<NUMBER>(soursePI, targetPI, (NDAT)this->nS);
    if(this->A  != NULL) cpy3D<NUMBER>(sourseA,  targetA,  (NDAT)this->nZ, (NDAT)this->nS, (NDAT)this->nS);
    if(this->B  != NULL) cpy3D<NUMBER>(sourseB,  targetB,  (NDAT)this->nZ, (NDAT)this->nS, (NDAT)this->nO);
}

void FitBitSlicedAB::add(NUMBER *soursePI, NUMBER ***sourseA, NUMBER ***sourseB, NUMBER *targetPI, NUMBER ***targetA, NUMBER ***targetB){
    if(this->pi != NULL) add1DNumbersWeighted(soursePI, targetPI, this->nS, 1.0);
    if(this->A  != NULL) add3DNumbersWeighted(sourseA,  targetA,  this->nZ, this->nS, this->nS, 1.0);
    if(this->B  != NULL) add3DNumbersWeighted(sourseB,  targetB,  this->nZ, this->nS, this->nO, 1.0);
}

void FitBitSlicedAB::destroy(NUMBER* &a_PI, NUMBER*** &a_A, NUMBER*** &a_B) {
    if(this->pi != NULL && a_PI != NULL) free(a_PI);
    if(this->A  != NULL && a_A  != NULL) free3D<NUMBER>(a_A, (NDAT)this->nZ, (NDAT)this->nS);
    if(this->B  != NULL && a_B  != NULL) free3D<NUMBER>(a_B, (NDAT)this->nZ, (NDAT)this->nS);
    a_PI = NULL;
    a_A  = NULL;
    a_B  = NULL;
}

void FitBitSlicedAB::init(enum FIT_BIT_SLOT fbs){
    switch (fbs) {
        case FBS_PAR:
            init(this->pi, this->A, this->B);
            break;
        case FBS_PARm1:
            init(this->PIm1, this->Am1, this->Bm1);
            break;
        case FBS_PARm2:
            init(this->PIm2, this->Am2, this->Bm2);
            break;
        case FBS_GRAD:
            init(this->gradPI, this->gradA, this->gradB);
            break;
        case FBS_GRADm1:
            init(this->gradPIm1, this->gradAm1, this->gradBm1);
            break;
        case FBS_PARcopy:
            init(this->PIcopy, this->Acopy, this->Bcopy);
            break;
        case FBS_DIR:
            init(this->dirPI, this->dirA, this->dirB);
            break;
        case FBS_DIRm1:
            init(this->dirPIm1, this->dirAm1, this->dirBm1);
            break;
        default:
            break;
    }
}

void FitBitSlicedAB::toZero(enum FIT_BIT_SLOT fbs){
    switch (fbs) {
        case FBS_PAR:
            toZero(this->pi, this->A, this->B);
            break;
        case FBS_PARm1:
            toZero(this->PIm1, this->Am1, this->Bm1);
            break;
        case FBS_PARm2:
            toZero(this->PIm2, this->Am2, this->Bm2);
            break;
        case FBS_GRAD:
            toZero(this->gradPI, this->gradA, this->gradB);
            break;
        case FBS_GRADm1:
            toZero(this->gradPIm1, this->gradAm1, this->gradBm1);
            break;
        case FBS_PARcopy:
            toZero(this->PIcopy, this->Acopy, this->Bcopy);
            break;
        case FBS_DIR:
            toZero(this->dirPI, this->dirA, this->dirB);
            break;
        case FBS_DIRm1:
            toZero(this->dirPIm1, this->dirAm1, this->dirBm1);
            break;
        default:
            break;
    }
}

void FitBitSlicedAB::destroy(enum FIT_BIT_SLOT fbs){
    switch (fbs) {
        case FBS_PAR:
            destroy(this->pi, this->A, this->B);
            break;
        case FBS_PARm1:
            destroy(this->PIm1, this->Am1, this->Bm1);
            break;
        case FBS_PARm2:
            destroy(this->PIm2, this->Am2, this->Bm2);
            break;
        case FBS_GRAD:
            destroy(this->gradPI, this->gradA, this->gradB);
            break;
        case FBS_GRADm1:
            destroy(this->gradPIm1, this->gradAm1, this->gradBm1);
            break;
        case FBS_PARcopy:
            destroy(this->PIcopy, this->Acopy, this->Bcopy);
            break;
        case FBS_DIR:
            destroy(this->dirPI, this->dirA, this->dirB);
            break;
        case FBS_DIRm1:
            destroy(this->dirPIm1, this->dirAm1, this->dirBm1);
            break;
        default:
            break;
    }
}

void FitBitSlicedAB::get(enum FIT_BIT_SLOT fbs, NUMBER* &a_PI, NUMBER*** &a_A, NUMBER*** &a_B) {
    switch (fbs) {
        case FBS_PAR:
            a_PI = this->pi;
            a_A  = this->A;
            a_B  = this->B;
            break;
        case FBS_PARm1:
            a_PI = this->PIm1;
            a_A  = this->Am1;
            a_B  = this->Bm1;
            break;
        case FBS_PARm2:
            a_PI = this->PIm2;
            a_A  = this->Am2;
            a_B  = this->Bm2;
            break;
        case FBS_GRAD:
            a_PI = this->gradPI;
            a_A  = this->gradA;
            a_B  = this->gradB;
            break;
        case FBS_GRADm1:
            a_PI = this->gradPIm1;
            a_A  = this->gradAm1;
            a_B  = this->gradBm1;
            break;
        case FBS_PARcopy:
            a_PI = this->PIcopy;
            a_A  = this->Acopy;
            a_B  = this->Bcopy;
            break;
        case FBS_DIR:
            a_PI = this->dirPI;
            a_A  = this->dirA;
            a_B  = this->dirB;
            break;
        case FBS_DIRm1:
            a_PI = this->dirPIm1;
            a_A  = this->dirAm1;
            a_B  = this->dirBm1;
            break;
        default:
            break;
    }
}

void FitBitSlicedAB::copy(enum FIT_BIT_SLOT sourse_fbs, enum FIT_BIT_SLOT target_fbs) {
    NUMBER *soursePI = NULL;
    NUMBER ***sourseA = NULL;
    NUMBER ***sourseB = NULL;
    get(sourse_fbs, soursePI, sourseA, sourseB);
    NUMBER *targetPI = NULL;
    NUMBER ***targetA = NULL;
    NUMBER ***targetB = NULL;
    get(target_fbs, targetPI, targetA, targetB);
    
    copy(soursePI, sourseA, sourseB, targetPI, targetA, targetB);
}

void FitBitSlicedAB::add(enum FIT_BIT_SLOT sourse_fbs, enum FIT_BIT_SLOT target_fbs) {
    NUMBER *soursePI = NULL;
    NUMBER ***sourseA = NULL;
    NUMBER ***sourseB = NULL;
    get(sourse_fbs, soursePI, sourseA, sourseB);
    NUMBER *targetPI = NULL;
    NUMBER ***targetA = NULL;
    NUMBER ***targetB = NULL;
    get(target_fbs, targetPI, targetA, targetB);
    
    add(soursePI, sourseA, sourseB, targetPI, targetA, targetB);
}

bool FitBitSlicedAB::checkConvergence(FitResult *fr) {

	NUMBER critetion = 0;
    for(NPAR i=0; i<this->nS; i++)
        if(this->pi != NULL) critetion += pow( this->pi[i]-this->PIm1[i], 2 )/*:0*/;

    for(NPAR z=0; z<this->nZ; z++)
        for(NPAR i=0; i<this->nS; i++)
        {
            for(NPAR j=0; (this->A != NULL) && j<this->nS; j++) {
                critetion += pow(this->A[z][i][j] - this->Am1[z][i][j],2);
            }
            for(NPAR k=0; (this->B != NULL) && k<this->nO; k++) {
                critetion += pow(this->B[z][i][k] - this->Bm1[z][i][k],2);
            }
        }
	return sqrt(critetion) < this->tol; // double the truth or false
        
//    return (fr->pOmid - fr->pO) < this->tol;
}

void FitBitSlicedAB::doLog10ScaleGentle(enum FIT_BIT_SLOT fbs) {
    // fbs - gradient or direction
    NUMBER *a_PI = NULL;
    NUMBER ***a_A = NULL;
    NUMBER ***a_B = NULL;
    get(fbs, a_PI, a_A, a_B);
	if(this->pi != NULL) doLog10Scale1DGentle(a_PI, this->pi, this->nS);
    if(this->A  != NULL)
        for(NPAR z=0; z<this->nZ; z++)
            doLog10Scale2DGentle(a_A[z],  this->A[z], this->nS, this->nS);
//        doLog10Scale3DGentle(a_A,  this->A,  this->nZ, this->nS, this->nS);
	if(this->B  != NULL)
        for(NPAR z=0; z<this->nZ; z++)
            doLog10Scale2DGentle(a_B[z],  this->B[z], this->nS, this->nO);
//        doLog10Scale3DGentle(a_B,  this->B,  this->nZ, this->nS, this->nO);
}

void FitBitSlicedAB::addL2Penalty(enum FIT_BIT_VAR fbv, param* param, NUMBER factor) {
    NPAR i, j, m, z;
    if(param->Cslices==0) return;
    NUMBER C = param->Cw[this->Cslice];
    switch (fbv) {
        case FBV_PI:
            for(i=0; i<this->nS; i++)
                this->gradPI[i] += factor * L2penalty(C, this->pi[i], param->Ccenters[ this->Cslice * 3 + 0] );
            break;
        case FBV_A:
            for(z=0; z<this->nZ; z++)
                for(i=0; i<this->nS; i++)
                    for(j=0; j<this->nS; j++)
                        this->gradA[z][i][j] += factor * L2penalty(C, this->A[z][i][j], param->Ccenters[ this->Cslice * 3 + 1] );
            break;
        case FBV_B:
            for(z=0; z<this->nZ; z++)
             for(i=0; i<this->nS; i++)
                 for(m=0; m<this->nO; m++)
                     this->gradB[z][i][m] += factor * L2penalty(C, this->B[z][i][m], param->Ccenters[ this->Cslice * 3 + 2] );
            break;
            
        default:
            fprintf(stderr,"Error, there is no such FitBitSlicedA variable\n");
            break;
    }
}

