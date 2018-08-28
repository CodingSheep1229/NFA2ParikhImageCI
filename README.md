# NFA2Parikh

Convert Nondeterministic Finite Automaton to Parikh Images in z3 format
<br>
this method is based on
> Helmut Seidl, Thomas Schwentick, Anca Muscholl, Peter Habermehl. Counting in trees for free. Josep Díaz, Juhani Karhumäki, Arto Lepistö and Donald Sannella. 31st International Colloquium on Automata, Languages and Programming (ICALP’04), 2004, Turku, Finland. Springer Verlag, pp.1136-1149, 2004, 3142. <hal-00159525>

click [here](https://github.com/Z3Prover/z3) for z3

## Usage
```
$ bash dofile.sh
```

## Input Format:
state_num, terminal_num, alphabet_num, transition_num<br>
states<br>
initial state<br>
terminal states<br>
alphabets<br>
transitions1(p,a,q)<br>
transitions2(p,a,q)<br>
.<br>
.<br>
.<br>
### Example: a(b|c)*
![NFA](https://i.imgur.com/iSZEUZj.png)
```
2 1 3 3
q0 q1
q0
q1
a b c
qo a q1
q1 b q1
q1 c q1
```
### Output:
```
(declare-const r_a Int)
(declare-const x_q0_a_q1 Int)
(declare-const r_b Int)
(declare-const x_q1_b_q1 Int)
(declare-const r_c Int)
(declare-const x_q1_c_q1 Int)
(declare-const out_q0 Int)
(declare-const out_q1 Int)
(declare-const in_q0 Int)
(declare-const in_q1 Int)
(declare-const start_q0 Bool)
(declare-const start_q1 Bool)
(declare-const t_q0 Int)
(declare-const t_q1 Int)
(declare-const flag_q0_1 Bool)
(declare-const flag_q0_2 Bool)
(declare-const flag_q0_3 Bool)
(declare-const flag_q1_1 Bool)
(declare-const flag_q1_2 Bool)
(declare-const flag_q1_3 Bool)
(assert (>= r_a 0))
(assert (>= x_q0_a_q1 0))
(assert (>= r_b 0))
(assert (>= x_q1_b_q1 0))
(assert (>= r_c 0))
(assert (>= x_q1_c_q1 0))
(assert (>= out_q0 0))
(assert (>= out_q1 0))
(assert (>= in_q0 0))
(assert (>= in_q1 0))
(assert (>= t_q0 0))
(assert (<= t_q0 1))
(assert (>= t_q1 0))
(assert (<= t_q1 1))
(assert (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (= r_a x_q0_a_q1 )(= r_b x_q1_b_q1 ))(= r_c x_q1_c_q1 ))(= out_q0 x_q0_a_q1 ))(= out_q1 (+ x_q1_b_q1 x_q1_c_q1 )))(= in_q0 0 ))(= in_q1 (+ x_q0_a_q1 (+ x_q1_b_q1 x_q1_c_q1 ))))start_q0 )(not  start_q1 ))(= t_q0 0 ))(= 1 t_q1 ))(or (or flag_q0_1 flag_q0_2 )flag_q0_3 ))(= flag_q0_1 (and (and (not start_q0  )(= t_q0 1 ))(= in_q0 (+ out_q0 1 )))))(= flag_q0_2 (and (and start_q0 (= t_q0 0 ))(= in_q0 (- out_q0 1 )))))(= flag_q0_3 (and (= in_q0 out_q0 )(not (xor start_q0 (= t_q0 1 )) ))))(or (or flag_q1_1 flag_q1_2 )flag_q1_3 ))(= flag_q1_1 (and (and (not start_q1  )(= t_q1 1 ))(= in_q1 (+ out_q1 1 )))))(= flag_q1_2 (and (and start_q1 (= t_q1 0 ))(= in_q1 (- out_q1 1 )))))(= flag_q1_3 (and (= in_q1 out_q1 )(not (xor start_q1 (= t_q1 1 )) )))))
(check-sat)
(get-model)
```

## Variables description
#### x_q0_a_q1 :
the number of times q0 traversed to q1 reading "a"<br>

#### in_q0 :
the total number of times other states traversed to q0<br>

#### out_q0 :
the total number of times q0 traversed to other states<br>

#### start_q0 :
whether q0 is the initial state<br>

#### start_q0 :
whether q0 is an accept state<br>

#### t_q0 :
whether q0 is the terminal state<br>

#### r_a :
the total number of times "a" is read<br>

#### flag_q0_1
q0 is the initial state<br>

#### flag_q0_2
q0 is the terminal state<br>

#### flag_q0_3
q0 is an intermediate state or both initial and terminal state<br>
