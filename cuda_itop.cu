#include <cuda.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif
__global__ void itop_kernel(const uint8_t* const in, uint8_t* out, const int data_len, const int thread_len)
{
    int offset = (blockDim.x * blockIdx.x * thread_len) + (blockIdx.x * thread_len);
    uint8_t* out_y = out + offset;
    uint8_t* out_b = out_y + (data_len / 3);
    uint8_t* out_r = out_b + (data_len / 3);
    for(int i = offset; i < thread_len + offset && i < data_len;)
    {
        *out_y++ = in[i++];
        *out_b++ = in[i++];
        *out_r++ = in[i++];
    }
}

__global__ void ptoi_kernel(const uint8_t * const in_y,
                            const uint8_t*  const in_b,
                            const uint8_t*  const in_r,
                            uint8_t* out, int data_len, int thread_len)
{
    int oset_main=(blockDim.x*blockIdx.x*thread_len)+(threadIdx.x*thread_len);
    for(int i=oset_main,j=oset_main;i<thread_len+oset_main&&i<data_len;++j)
    {
        out[i] = in_y[j];
        ++i;
        out[i] = in_b[j];
        ++i;
        out[i] = in_r[j];
        ++i;
    }
}

uint8_t* cuda_interstitial_to_planar(uint8_t* data, int data_len)
{
    if(data_len%3)
    {
        printf("Error: data_len must be a multiple of 3\n");
        return NULL;
    }
    int channel_len = data_len/3;
    int num_threads = channel_len/256;
    uint8_t* h_out = (uint8_t*)malloc(data_len);
    uint8_t* d_in, *d_out;
    cudaMalloc((void**)&d_in,data_len);
    cudaMalloc((void**)&d_out,data_len);
    cudaMemcpy(d_in,data,data_len,cudaMemcpyHostToDevice);
    printf("3 blocks and %d threads\n",num_threads);
    printf("thread len: %d\n",data_len/(3*num_threads));
    itop_kernel<<<3,num_threads>>>(d_in,d_out,data_len,data_len/(3*num_threads));
    cudaMemcpy(h_out,d_out,data_len,cudaMemcpyDeviceToHost);
    cudaFree(d_in);
    cudaFree(d_out);
    return h_out;
}
#ifdef __cplusplus
}
#endif
