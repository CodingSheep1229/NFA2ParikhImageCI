#include <iostream>
#include <string>
#include "gtest/gtest.h"

#include "NFA.h"

TEST(NFA, nfa1) {
	string in = "2 1 3 3\nq0 q1\nq0\nq1\na b c\nq0 a q1\nq1 b q1\nq1 c q1";
	string out = "(declare-const r_a Int)\n(declare-const x_q0_a_q1 Int)\n(declare-const r_b Int)\n(declare-const x_q1_b_q1 Int)\n(declare-const r_c Int)\n(declare-const x_q1_c_q1 Int)\n(declare-const out_q0 Int)\n(declare-const out_q1 Int)\n(declare-const in_q0 Int)\n(declare-const in_q1 Int)\n(declare-const start_q0 Bool)\n(declare-const start_q1 Bool)\n(declare-const t_q0 Int)\n(declare-const t_q1 Int)\n(declare-const flag_q0_1 Bool)\n(declare-const flag_q0_2 Bool)\n(declare-const flag_q0_3 Bool)\n(declare-const flag_q1_1 Bool)\n(declare-const flag_q1_2 Bool)\n(declare-const flag_q1_3 Bool)\n(assert (>= r_a 0))\n(assert (>= x_q0_a_q1 0))\n(assert (>= r_b 0))\n(assert (>= x_q1_b_q1 0))\n(assert (>= r_c 0))\n(assert (>= x_q1_c_q1 0))\n(assert (>= out_q0 0))\n(assert (>= out_q1 0))\n(assert (>= in_q0 0))\n(assert (>= in_q1 0))\n(assert (>= t_q0 0))\n(assert (<= t_q0 1))\n(assert (>= t_q1 0))\n(assert (<= t_q1 1))\n(assert (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (= r_a x_q0_a_q1 )(= r_b x_q1_b_q1 ))(= r_c x_q1_c_q1 ))(= out_q0 x_q0_a_q1 ))(= out_q1 (+ x_q1_b_q1 x_q1_c_q1 )))(= in_q0 0 ))(= in_q1 (+ x_q0_a_q1 (+ x_q1_b_q1 x_q1_c_q1 ))))start_q0 )(not  start_q1 ))(= t_q0 0 ))(= 1 t_q1 ))(or (or flag_q0_1 flag_q0_2 )flag_q0_3 ))(= flag_q0_1 (and (and (not start_q0  )(= t_q0 1 ))(= in_q0 (+ out_q0 1 )))))(= flag_q0_2 (and (and start_q0 (= t_q0 0 ))(= in_q0 (- out_q0 1 )))))(= flag_q0_3 (and (= in_q0 out_q0 )(not (xor start_q0 (= t_q0 1 )) ))))(or (or flag_q1_1 flag_q1_2 )flag_q1_3 ))(= flag_q1_1 (and (and (not start_q1  )(= t_q1 1 ))(= in_q1 (+ out_q1 1 )))))(= flag_q1_2 (and (and start_q1 (= t_q1 0 ))(= in_q1 (- out_q1 1 )))))(= flag_q1_3 (and (= in_q1 out_q1 )(not (xor start_q1 (= t_q1 1 )) )))))\n(check-sat)\n(get-model)\n";
	EXPECT_EQ(test(in),out);
}
