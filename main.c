/*
 **************************************************************************************
 *       Filename:  main.c
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2017-09-14 21:51:55
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#define LOG_TAG "main"

#include <errno.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>

#include "log.h"

int chained_bio() {
    BIO* bmem = BIO_new(BIO_f_buffer());
    BIO* bstd = BIO_new_fp(stdout, BIO_NOCLOSE);
    BIO* blog = BIO_new_file("ssl.log", "a+");
    if(!bmem || !bstd || !blog) {
        loge("fail to new bio: %p %p %p", bmem, bstd, blog);
        return -ENOMEM;
    }
    BIO_push(bmem, blog);

    BIO_puts(bmem, "hello openssl\n");
    BIO_flush(bmem);

    BIO_free(blog);
    BIO_free(bstd);
    BIO_free(bmem);
    return 0;
}

int main() {
    chained_bio();
    return 0;
}

/********************************** END **********************************************/
