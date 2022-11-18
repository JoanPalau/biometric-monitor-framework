#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class DecisionTree {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        if (x[1] <= 0.5) {
                            if (x[0] <= 0.5) {
                                if (x[2] <= 138.67450714111328) {
                                    if (x[2] <= 46.46964073181152) {
                                        return 3;
                                    }

                                    else {
                                        return 0;
                                    }
                                }

                                else {
                                    return 3;
                                }
                            }

                            else {
                                if (x[0] <= 2.5) {
                                    if (x[2] <= 87.90760040283203) {
                                        return 1;
                                    }

                                    else {
                                        return 2;
                                    }
                                }

                                else {
                                    if (x[2] <= 43.07152557373047) {
                                        return 3;
                                    }

                                    else {
                                        return 1;
                                    }
                                }
                            }
                        }

                        else {
                            if (x[1] <= 1.5) {
                                if (x[2] <= 94.48748779296875) {
                                    if (x[2] <= 48.55728530883789) {
                                        return 3;
                                    }

                                    else {
                                        return 2;
                                    }
                                }

                                else {
                                    if (x[0] <= 1.5) {
                                        return 3;
                                    }

                                    else {
                                        return 3;
                                    }
                                }
                            }

                            else {
                                return 3;
                            }
                        }
                    }

                protected:
                };
            }
        }
    }