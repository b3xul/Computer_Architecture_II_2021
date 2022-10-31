#!/usr/bin/python

speedup_enhanced=2

instruction_enhanced=238136
latency_of_instruction=5
cc_enhanced=39815912

fraction_enhanced=instruction_enhanced*latency_of_instruction/cc_enhanced
echo 'fraction_enhanced=fraction_enhanced'

speedup_overall_by_amdahl=1/((1-fraction_enhanced)+fraction_enhanced/speedup_enhanced))
echo 'speedup_overall_by_amdahl=speedup_overall_by_amdahl'