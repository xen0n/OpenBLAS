/***************************************************************************
Copyright (c) 2014, The OpenBLAS Project
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in
the documentation and/or other materials provided with the
distribution.
3. Neither the name of the OpenBLAS project nor the names of
its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE OPENBLAS PROJECT OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

#define HAVE_KERNEL_8 1
static void daxpy_kernel_8( BLASLONG n, FLOAT *x, FLOAT *y , FLOAT *alpha) __attribute__ ((noinline));

static void daxpy_kernel_8( BLASLONG n, FLOAT *x, FLOAT *y, FLOAT *alpha)
{


	BLASLONG register i = 0;

	__asm__  __volatile__
	(
	"vbroadcastsd		(%4), %%ymm0		    \n\t"  // alpha	

	".align 16				            \n\t"
	"1:				            \n\t"
	"vmovups	  (%3,%0,8), %%ymm8         \n\t"
	"vmovups	32(%3,%0,8), %%ymm9         \n\t"
	"vmovups	64(%3,%0,8), %%ymm10        \n\t"
	"vmovups	96(%3,%0,8), %%ymm11        \n\t"
	"vmovups       128(%3,%0,8), %%ymm12        \n\t"
	"vmovups       160(%3,%0,8), %%ymm13        \n\t"
	"vmovups       192(%3,%0,8), %%ymm14        \n\t"
	"vmovups       224(%3,%0,8), %%ymm15        \n\t"

	"vmulpd		(%2,%0,8), %%ymm0, %%ymm1		\n\t"
	"vmulpd	      32(%2,%0,8), %%ymm0, %%ymm2		\n\t"
	"vaddpd		%%ymm8 , %%ymm1, %%ymm8		     \n\t"
	"vmulpd	      64(%2,%0,8), %%ymm0, %%ymm3		\n\t"
	"vaddpd		%%ymm9 , %%ymm2, %%ymm9		     \n\t"
	"vmulpd	      96(%2,%0,8), %%ymm0, %%ymm4		\n\t"
	"vaddpd		%%ymm10, %%ymm3, %%ymm10	     \n\t"
	"vmulpd	     128(%2,%0,8), %%ymm0, %%ymm5		\n\t"
	"vaddpd		%%ymm11, %%ymm4, %%ymm11	     \n\t"
	"vmulpd	     160(%2,%0,8), %%ymm0, %%ymm6		\n\t"
	"vaddpd		%%ymm12, %%ymm5, %%ymm12	     \n\t"
	"vmulpd	     192(%2,%0,8), %%ymm0, %%ymm7		\n\t"
	"vmulpd	     224(%2,%0,8), %%ymm0, %%ymm1	     \n\t"

	"vaddpd		%%ymm13, %%ymm6, %%ymm13	     \n\t"
	"vmovups	%%ymm8 ,   (%3,%0,8)		     \n\t"
	"vaddpd		%%ymm14, %%ymm7, %%ymm14	     \n\t"
	"vmovups	%%ymm9 , 32(%3,%0,8)		     \n\t"
	"vaddpd		%%ymm15, %%ymm1, %%ymm15	     \n\t"
	"vmovups	%%ymm10, 64(%3,%0,8)		     \n\t"
	"vmovups	%%ymm11, 96(%3,%0,8)		     \n\t"
	"vmovups	%%ymm12,128(%3,%0,8)		     \n\t"
	"vmovups	%%ymm13,160(%3,%0,8)		     \n\t"
	"vmovups	%%ymm14,192(%3,%0,8)		     \n\t"
	"vmovups	%%ymm15,224(%3,%0,8)		     \n\t"

	"addq		$32, %0	  	 	             \n\t"
	"subq	        $32, %1			             \n\t"		
	"jnz		1b		             \n\t"
	"vzeroupper				     \n\t"

	:
        : 
          "r" (i),	// 0	
	  "r" (n),  	// 1
          "r" (x),      // 2
          "r" (y),      // 3
          "r" (alpha)   // 4
	: "cc", 
	  "%xmm0", "%xmm1", "%xmm2", "%xmm3", 
	  "%xmm4", "%xmm5", "%xmm6", "%xmm7", 
	  "%xmm8", "%xmm9", "%xmm10", "%xmm11",
	  "%xmm12", "%xmm13", "%xmm14", "%xmm15",
	  "memory"
	);

} 

