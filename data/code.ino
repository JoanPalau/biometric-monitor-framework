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
                                return 0;
                            }

                            else {
                                if (x[3] <= 19.77481746673584) {
                                    if (x[2] <= 90.50672149658203) {
                                        if (x[0] <= 1.5) {
                                            return 1;
                                        }

                                        else {
                                            return 2;
                                        }
                                    }

                                    else {
                                        if (x[3] <= -78.71746826171875) {
                                            return 0;
                                        }

                                        else {
                                            return 2;
                                        }
                                    }
                                }

                                else {
                                    if (x[0] <= 1.5) {
                                        if (x[3] <= 33.06558132171631) {
                                            return 1;
                                        }

                                        else {
                                            return 2;
                                        }
                                    }

                                    else {
                                        if (x[0] <= 2.5) {
                                            return 3;
                                        }

                                        else {
                                            return 0;
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[1] <= 1.5) {
                                if (x[2] <= 96.09757232666016) {
                                    if (x[2] <= 48.26219177246094) {
                                        return 3;
                                    }

                                    else {
                                        if (x[3] <= -34.908775329589844) {
                                            return 2;
                                        }

                                        else {
                                            return 2;
                                        }
                                    }
                                }

                                else {
                                    if (x[0] <= 1.5) {
                                        if (x[0] <= 0.5) {
                                            return 3;
                                        }

                                        else {
                                            return 2;
                                        }
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