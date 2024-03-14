typedef struct {
    rmulti* down;
    rmulti* up;
} mi_r;

typedef struct {
    mi_r* r;
    mi_r* i;
} mi_c;

mi_r* mi_rallocate() {
    mi_r* mir = (mi_r*)malloc(sizeof(mi_r));
    mir->down = rallocate();
    mir->up = rallocate();
    return mir;
}

mi_c* mi_callocate() {
    mi_c* mic = (mi_c*)malloc(sizeof(mi_c));
    mic->r = mi_rallocate();
    mic->i = mi_rallocate();
    return mic;
}

mi_r* mi_rfree(mi_r* x) {
    x->down = rmfree(x->down);
    x->up = rmfree(x->up);
    return NULL;
}

mi_c* mi_cfree(mi_c* x) {
    x->r = mi_rfree(x->r);
    x->i = mi_rfree(x->i);
    return NULL;
}

void mir_mir_set(mi_r* z, mi_r* x) {
    mpfr_set(z->down, x->down, MPFR_RNDD);
    mpfr_set(z->up, x->up, MPFR_RNDU);
}

void mir_str_set(mi_r* z, char* x) {
    mpfr_set_str(z->down, x, 10, MPFR_RNDD);
    mpfr_set_str(z->up, x, 10, MPFR_RNDU);
}

void mir_str_set_dot(mi_r* z, char* x) {
    mpfr_set_str(z->down, x, 10, MPFR_RNDN);
    mpfr_set_str(z->up, x, 10, MPFR_RNDN);
}

void mir_rr_add(mi_r* z, rmulti* x, rmulti* y) {
    mpfr_add(z->down, x, y, MPFR_RNDD);
    mpfr_add(z->up, x, y, MPFR_RNDU);
}

void mir_rr_sub(mi_r* z, rmulti* x, rmulti* y) {
    mpfr_sub(z->down, x, y, MPFR_RNDD);
    mpfr_sub(z->up, x, y, MPFR_RNDU);
}

void mir_rr_mul(mi_r* z, rmulti* x, rmulti* y) {
    mpfr_mul(z->down, x, y, MPFR_RNDD);
    mpfr_mul(z->up, x, y, MPFR_RNDU);
}

void mir_rr_div(mi_r* z, rmulti* x, rmulti* y) {
    mpfr_div(z->down, x, y, MPFR_RNDD);
    mpfr_div(z->up, x, y, MPFR_RNDU);
}

void mir_r_sqrt(mi_r* z, rmulti* x) {
    mpfr_sqrt(z->down, x, MPFR_RNDD);
    mpfr_sqrt(z->up, x, MPFR_RNDU);
}

void mir_r_rec(mi_r* z, rmulti* x) {
    mpfr_rec_sqrt(z->down, x, MPFR_RNDD);
    mpfr_rec_sqrt(z->up, x, MPFR_RNDU);
}

void mir_rr_pow(mi_r* z, rmulti* x, rmulti* y) {
    mpfr_pow(z->down, x, y, MPFR_RNDD);
    mpfr_pow(z->up, x, y, MPFR_RNDU);
}

void mir_rr_pow_plusnbits(mi_r* z, rmulti* x, rmulti* y, int n) {
    rmulti *x0, *y0;
    mi_r *z0;

    set_default_prec(mpfr_get_prec(x) + n);

    x0 = rallocate();
    y0 = rallocate();
    z0 = mi_rallocate();

    mpfr_set(x0, x, MPFR_RNDN);
    mpfr_set(y0, y, MPFR_RNDN);

    mir_rr_pow(z0, x0, y0);

    set_default_prec(mpfr_get_prec(x));

    mir_mir_set(z, z0);

    x0 = rmfree(x0);
    y0 = rmfree(y0);
    z0 = mi_rfree(z0);
}

void mir_rr_pow_timesnbits(mi_r* z, rmulti* x, rmulti* y, int n) {
    rmulti *x0, *y0;
    mi_r *z0;

    set_default_prec(mpfr_get_prec(x) * n);

    x0 = rallocate();
    y0 = rallocate();
    z0 = mi_rallocate();

    mpfr_set(x0, x, MPFR_RNDN);
    mpfr_set(y0, y, MPFR_RNDN);

    mir_rr_pow(z0, x0, y0);

    set_default_prec(mpfr_get_prec(x));

    mir_mir_set(z, z0);

    x0 = rmfree(x0);
    y0 = rmfree(y0);
    z0 = mi_rfree(z0);
}


void mir_r_log(mi_r* z, rmulti* x) {
    mpfr_log(z->down, x, MPFR_RNDD);
    mpfr_log(z->up, x, MPFR_RNDU);
}

void mir_r_log2(mi_r* z, rmulti* x) {
    mpfr_log2(z->down, x, MPFR_RNDD);
    mpfr_log2(z->up, x, MPFR_RNDU);
}

void mir_r_log10(mi_r* z, rmulti* x) {
    mpfr_log10(z->down, x, MPFR_RNDD);
    mpfr_log10(z->up, x, MPFR_RNDU);
}

void mir_r_exp(mi_r* z, rmulti* x) {
    mpfr_exp(z->down, x, MPFR_RNDD);
    mpfr_exp(z->up, x, MPFR_RNDU);
}

void mir_r_exp_plusnbits(mi_r* z, rmulti* x, int n) {
    rmulti *x0;
    mi_r *z0;

    set_default_prec(mpfr_get_prec(x) + n);

    x0 = rallocate();
    z0 = mi_rallocate();

    mpfr_set(x0, x, MPFR_RNDN);

    mir_r_exp(z0, x0);

    set_default_prec(mpfr_get_prec(x));

    mir_mir_set(z, z0);

    x0 = rmfree(x0);
    z0 = mi_rfree(z0);
}

void mir_r_exp_timesnbits(mi_r* z, rmulti* x, int n) {
    rmulti *x0;
    mi_r *z0;

    set_default_prec(mpfr_get_prec(x) * n);

    x0 = rallocate();
    z0 = mi_rallocate();

    mpfr_set(x0, x, MPFR_RNDN);

    mir_r_exp(z0, x0);

    set_default_prec(mpfr_get_prec(x));

    mir_mir_set(z, z0);

    x0 = rmfree(x0);
    z0 = mi_rfree(z0);
}

void mir_r_exp2(mi_r* z, rmulti* x) {
    mpfr_exp2(z->down, x, MPFR_RNDD);
    mpfr_exp2(z->up, x, MPFR_RNDU);
}

void mir_r_exp10(mi_r* z, rmulti* x) {
    mpfr_exp10(z->down, x, MPFR_RNDD);
    mpfr_exp10(z->up, x, MPFR_RNDU);
}

void mir_r_cos(mi_r* z, rmulti* x) {
    mpfr_cos(z->down, x, MPFR_RNDD);
    mpfr_cos(z->up, x, MPFR_RNDU);
}

void mir_r_sin(mi_r* z, rmulti* x) {
    mpfr_sin(z->down, x, MPFR_RNDD);
    mpfr_sin(z->up, x, MPFR_RNDU);
}

void mir_r_tan(mi_r* z, rmulti* x) {
    mpfr_tan(z->down, x, MPFR_RNDD);
    mpfr_tan(z->up, x, MPFR_RNDU);
}

void mir_r_sec(mi_r* z, rmulti* x) {
    mpfr_sec(z->down, x, MPFR_RNDD);
    mpfr_sec(z->up, x, MPFR_RNDU);
}

void mir_r_csc(mi_r* z, rmulti* x) {
    mpfr_csc(z->down, x, MPFR_RNDD);
    mpfr_csc(z->up, x, MPFR_RNDU);
}

void mir_r_cot(mi_r* z, rmulti* x) {
    mpfr_cot(z->down, x, MPFR_RNDD);
    mpfr_cot(z->up, x, MPFR_RNDU);
}

void mir_r_acos(mi_r* z, rmulti* x) {
    mpfr_acos(z->down, x, MPFR_RNDD);
    mpfr_acos(z->up, x, MPFR_RNDU);
}

void mir_r_asin(mi_r* z, rmulti* x) {
    mpfr_asin(z->down, x, MPFR_RNDD);
    mpfr_asin(z->up, x, MPFR_RNDU);
}

void mir_r_atan(mi_r* z, rmulti* x) {
    mpfr_atan(z->down, x, MPFR_RNDD);
    mpfr_atan(z->up, x, MPFR_RNDU);
}

void mir_r_cosh(mi_r* z, rmulti* x) {
    mpfr_cosh(z->down, x, MPFR_RNDD);
    mpfr_cosh(z->up, x, MPFR_RNDU);
}

void mir_r_sinh(mi_r* z, rmulti* x) {
    mpfr_sinh(z->down, x, MPFR_RNDD);
    mpfr_sinh(z->up, x, MPFR_RNDU);
}

void mir_r_tanh(mi_r* z, rmulti* x) {
    mpfr_tanh(z->down, x, MPFR_RNDD);
    mpfr_tanh(z->up, x, MPFR_RNDU);
}

void mir_r_sech(mi_r* z, rmulti* x) {
    mpfr_sech(z->down, x, MPFR_RNDD);
    mpfr_sech(z->up, x, MPFR_RNDU);
}

void mir_r_csch(mi_r* z, rmulti* x) {
    mpfr_csch(z->down, x, MPFR_RNDD);
    mpfr_csch(z->up, x, MPFR_RNDU);
}

void mir_r_coth(mi_r* z, rmulti* x) {
    mpfr_coth(z->down, x, MPFR_RNDD);
    mpfr_coth(z->up, x, MPFR_RNDU);
}

void mir_r_acosh(mi_r* z, rmulti* x) {
    mpfr_acosh(z->down, x, MPFR_RNDD);
    mpfr_acosh(z->up, x, MPFR_RNDU);
}

void mir_r_asinh(mi_r* z, rmulti* x) {
    mpfr_asinh(z->down, x, MPFR_RNDD);
    mpfr_asinh(z->up, x, MPFR_RNDU);
}

void mir_r_atanh(mi_r* z, rmulti* x) {
    mpfr_atanh(z->down, x, MPFR_RNDD);
    mpfr_atanh(z->up, x, MPFR_RNDU);
}

void mir_mirmir_add(mi_r* z, mi_r* x, mi_r* y) {
    mpfr_add(z->down, x->down, y->down, MPFR_RNDD);
    mpfr_add(z->up, x->up, y->up, MPFR_RNDU);
}

void mir_mirmir_sub(mi_r* z, mi_r* x, mi_r* y) {
    mpfr_sub(z->down, x->down, y->up, MPFR_RNDD);
    mpfr_sub(z->up, x->up, y->down, MPFR_RNDU);
}

void mir_mirmir_mul(mi_r* z, mi_r* x, mi_r* y) {
    rmulti *z_min, *z_max, *a;

    z_min = rallocate();
    z_max = rallocate();
    a = rallocate();

    mpfr_mul(z_min, x->down, y->down, MPFR_RNDD);
    mpfr_mul(a, x->down, y->up, MPFR_RNDD);
    if(mpfr_cmp(a, z_min) < 0) {
        mpfr_set(z_min, a, MPFR_RNDD);
    }
    mpfr_mul(a, x->up, y->down, MPFR_RNDD);
    if(mpfr_cmp(a, z_min) < 0) {
        mpfr_set(z_min, a, MPFR_RNDD);
    }
    mpfr_mul(a, x->up, y->up, MPFR_RNDD);
    if(mpfr_cmp(a, z_min) < 0) {
        mpfr_set(z_min, a, MPFR_RNDD);
    }
    mpfr_set(z->down, z_min, MPFR_RNDD);

    mpfr_mul(z_max, x->down, y->down, MPFR_RNDU);
    mpfr_mul(a, x->down, y->up, MPFR_RNDU);
    if(mpfr_cmp(a, z_max) > 0) {
        mpfr_set(z_max, a, MPFR_RNDU);
    }
    mpfr_mul(a, x->up, y->down, MPFR_RNDU);
    if(mpfr_cmp(a, z_max) > 0) {
        mpfr_set(z_max, a, MPFR_RNDU);
    }
    mpfr_mul(a, x->up, y->up, MPFR_RNDU);
    if(mpfr_cmp(a, z_max) < 0) {
        mpfr_set(z_max, a, MPFR_RNDU);
    }
    mpfr_set(z->up, z_max, MPFR_RNDU);

    z_min = rmfree(z_min);
    z_max = rmfree(z_max);
    a = rmfree(a);
}

void mir_mirmir_div(mi_r* z, mi_r* x, mi_r* y) {
    rmulti *z_min, *z_max, *a;

    z_min = rallocate();
    z_max = rallocate();
    a = rallocate();

    mpfr_div(z_min, x->down, y->down, MPFR_RNDD);
    mpfr_div(a, x->down, y->up, MPFR_RNDD);
    if(mpfr_cmp(a, z_min) < 0) {
        mpfr_set(z_min, a, MPFR_RNDD);
    }
    mpfr_div(a, x->up, y->down, MPFR_RNDD);
    if(mpfr_cmp(a, z_min) < 0) {
        mpfr_set(z_min, a, MPFR_RNDD);
    }
    mpfr_div(a, x->up, y->up, MPFR_RNDD);
    if(mpfr_cmp(a, z_min) < 0) {
        mpfr_set(z_min, a, MPFR_RNDD);
    }
    mpfr_set(z->down, z_min, MPFR_RNDD);

    mpfr_div(z_max, x->down, y->down, MPFR_RNDU);
    mpfr_div(a, x->down, y->up, MPFR_RNDU);
    if(mpfr_cmp(a, z_max) > 0) {
        mpfr_set(z_max, a, MPFR_RNDU);
    }
    mpfr_div(a, x->up, y->down, MPFR_RNDU);
    if(mpfr_cmp(a, z_max) > 0) {
        mpfr_set(z_max, a, MPFR_RNDU);
    }
    mpfr_div(a, x->up, y->up, MPFR_RNDU);
    if(mpfr_cmp(a, z_max) < 0) {
        mpfr_set(z_max, a, MPFR_RNDU);
    }
    mpfr_set(z->up, z_max, MPFR_RNDU);

    z_min = rmfree(z_min);
    z_max = rmfree(z_max);
    a = rmfree(a);
}

void mic_mic_set(mi_c* z, mi_c* x) {
    mir_mir_set(z->r, x->r);
    mir_mir_set(z->i, x->i);
}


void mic_strstr_set(mi_c* z, char* x, char* y) {
    mir_str_set(z->r, x);
    mir_str_set(z->i, y);
}

void mic_strstr_set_dot(mi_c* z, char* x, char* y) {
    mir_str_set_dot(z->r, x);
    mir_str_set_dot(z->i, y);
}

void mic_cc_add(mi_c* z, cmulti* x, cmulti* y) {
    mpfr_add(z->r->down, x->r, y->r, MPFR_RNDD);
    mpfr_add(z->r->up, x->r, y->r, MPFR_RNDU);
    mpfr_add(z->i->down, x->i, y->i, MPFR_RNDD);
    mpfr_add(z->i->up, x->i, y->i, MPFR_RNDU);
}

void mic_cc_sub(mi_c* z, cmulti* x, cmulti* y) {
    mpfr_sub(z->r->down, x->r, y->r, MPFR_RNDD);
    mpfr_sub(z->r->up, x->r, y->r, MPFR_RNDU);
    mpfr_sub(z->i->down, x->i, y->i, MPFR_RNDD);
    mpfr_sub(z->i->up, x->i, y->i, MPFR_RNDU);
}

void mic_micmic_add(mi_c* z, mi_c* x, mi_c* y) {
    mir_mirmir_add(z->r, x->r, y->r);
    mir_mirmir_add(z->i, x->i, y->i);
}

void mic_micmic_sub(mi_c* z, mi_c* x, mi_c* y) {
    mir_mirmir_sub(z->r, x->r, y->r);
    mir_mirmir_sub(z->i, x->i, y->i);
}

void mic_micmic_mul(mi_c* z, mi_c* x, mi_c* y) {
    mi_r *a, *b;

    a = mi_rallocate();
    b = mi_rallocate();

    mir_mirmir_mul(a, x->r, y->r);
    mir_mirmir_mul(b, x->i, y->i);
    mir_mirmir_sub(z->r, a, b);

    a = mi_rfree(a);
    b = mi_rfree(b);
    a = mi_rallocate();
    b = mi_rallocate();

    mir_mirmir_mul(a, x->r, y->i);
    mir_mirmir_mul(b, x->i, y->r);
    mir_mirmir_add(z->i, a, b);

    a = mi_rfree(a);
    b = mi_rfree(b);
}

void mic_micmic_mul_plusnbits(mi_c* z, mi_c* x, mi_c* y, int n) {
    mi_c *x0, *y0, *z0;

    set_default_prec(mpfr_get_prec(x->r->down) + n);

    x0 = mi_callocate();
    y0 = mi_callocate();
    z0 = mi_callocate();

    mic_mic_set(x0, x);
    mic_mic_set(y0, y);

    mic_micmic_mul(z0, x0, y0);

    set_default_prec(mpfr_get_prec(x->r->down));

    mic_mic_set(z, z0);

    x0 = mi_cfree(x0);
    y0 = mi_cfree(y0);
    z0 = mi_cfree(z0);
}

void mic_micmic_mul_timesnbits(mi_c* z, mi_c* x, mi_c* y, int n) {
    mi_c *x0, *y0, *z0;

    set_default_prec(mpfr_get_prec(x->r->down) * n);

    x0 = mi_callocate();
    y0 = mi_callocate();
    z0 = mi_callocate();

    mic_mic_set(x0, x);
    mic_mic_set(y0, y);

    mic_micmic_mul(z0, x0, y0);

    set_default_prec(mpfr_get_prec(x->r->down));

    mic_mic_set(z, z0);

    x0 = mi_cfree(x0);
    y0 = mi_cfree(y0);
    z0 = mi_cfree(z0);
}


void mic_micmic_mul_1ulp(mi_c* z, mi_c* x, mi_c* y) {
    mi_c *x0, *y0, *z0;

    set_default_prec((mpfr_get_prec(x->r->down) * 2) + 16);

    x0 = mi_callocate();
    y0 = mi_callocate();
    z0 = mi_callocate();

    mic_mic_set(x0, x);
    mic_mic_set(y0, y);

    mic_micmic_mul(z0, x0, y0);

    set_default_prec(mpfr_get_prec(x->r->down));

    mic_mic_set(z, z0);

    x0 = mi_cfree(x0);
    y0 = mi_cfree(y0);
    z0 = mi_cfree(z0);
}

void mic_micmic_div(mi_c* z, mi_c* x, mi_c* y) {
    mi_r *a, *b, *c, *d;

    a = mi_rallocate();
    b = mi_rallocate();
    c = mi_rallocate();
    d = mi_rallocate();

    mir_mirmir_mul(a, x->r, y->r);
    mir_mirmir_mul(b, x->i, y->i);
    mir_mirmir_add(c, a, b);

    a = mi_rfree(a);
    b = mi_rfree(b);
    a = mi_rallocate();
    b = mi_rallocate();

    mir_mirmir_mul(a, y->r, y->r);
    mir_mirmir_mul(b, y->i, y->i);
    mir_mirmir_add(d, a, b);

    mir_mirmir_div(z->r, c, d);

    a = mi_rfree(a);
    b = mi_rfree(b);
    c = mi_rfree(c);
    d = mi_rfree(d);
    a = mi_rallocate();
    b = mi_rallocate();
    c = mi_rallocate();
    d = mi_rallocate();

    mir_mirmir_mul(a, x->i, y->r);
    mir_mirmir_mul(b, x->r, y->i);
    mir_mirmir_sub(c, a, b);

    a = mi_rfree(a);
    b = mi_rfree(b);
    a = mi_rallocate();
    b = mi_rallocate();

    mir_mirmir_mul(a, y->r, y->r);
    mir_mirmir_mul(b, y->i, y->i);
    mir_mirmir_add(d, a, b);

    mir_mirmir_div(z->i, c, d);

    a = mi_rfree(a);
    b = mi_rfree(b);
    c = mi_rfree(c);
    d = mi_rfree(d);
}

void mic_micmic_div_plusnbits(mi_c* z, mi_c* x, mi_c* y, int n) {
    mi_c *x0, *y0, *z0;

    set_default_prec(mpfr_get_prec(x->r->down) + n);

    x0 = mi_callocate();
    y0 = mi_callocate();
    z0 = mi_callocate();

    mic_mic_set(x0, x);
    mic_mic_set(y0, y);

    mic_micmic_div(z0, x0, y0);

    set_default_prec(mpfr_get_prec(x->r->down));

    mic_mic_set(z, z0);

    x0 = mi_cfree(x0);
    y0 = mi_cfree(y0);
    z0 = mi_cfree(z0);
}

void mic_micmic_div_timesnbits(mi_c* z, mi_c* x, mi_c* y, int n) {
    mi_c *x0, *y0, *z0;

    set_default_prec(mpfr_get_prec(x->r->down) * n);

    x0 = mi_callocate();
    y0 = mi_callocate();
    z0 = mi_callocate();

    mic_mic_set(x0, x);
    mic_mic_set(y0, y);

    mic_micmic_div(z0, x0, y0);

    set_default_prec(mpfr_get_prec(x->r->down));

    mic_mic_set(z, z0);

    x0 = mi_cfree(x0);
    y0 = mi_cfree(y0);
    z0 = mi_cfree(z0);
}



void mic_micmic_div_1ulp(mi_c* z, mi_c* x, mi_c* y) {
    mi_c *x0, *y0, *z0;

    set_default_prec((mpfr_get_prec(x->r->down) * 2) + 16);
    
    x0 = mi_callocate();
    y0 = mi_callocate();
    z0 = mi_callocate();

    mic_mic_set(x0, x);
    mic_mic_set(y0, y);
    mic_mic_set(z0, z);

    mic_micmic_div(z0, x0, y0);

    set_default_prec(mpfr_get_prec(x->r->down));

    mic_mic_set(z, z0);

    x0 = mi_cfree(x0);
    y0 = mi_cfree(y0);
    z0 = mi_cfree(z0);
}