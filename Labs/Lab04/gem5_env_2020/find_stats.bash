#!/bin/bash

echo "AtomicSimpleCPU"
#cat ./AtomicSimpleCPU/m5out/stats.txt | grep -E 'sim_ticks|sim_insts|system.cpu.numCycles|system.cpu.cpi|system.cpu.committedInsts|host_seconds|system.cpu.fetch.Insts'
cat ./AtomicSimpleCPU/m5out/stats.txt | grep -E 'sim_ticks|sim_insts|system.cpu.numCycles|system.cpu.cpi|system.cpu.committedInsts|host_seconds|system.cpu.fetch.Insts|system.cpu.branchPred.condIncorrect|system.cpu.branchPred.condPredicted|system.cpu.branchPred.BTBHits'

echo "TimingSimpleCPU"
#cat ./TimingSimpleCPU/m5out/stats.txt | grep -E 'sim_ticks|sim_insts|system.cpu.numCycles|system.cpu.cpi|system.cpu.committedInsts|host_seconds|system.cpu.fetch.Insts'
cat ./TimingSimpleCPU/m5out/stats.txt | grep -E 'sim_ticks|sim_insts|system.cpu.numCycles|system.cpu.cpi|system.cpu.committedInsts|host_seconds|system.cpu.fetch.Insts|system.cpu.branchPred.condIncorrect|system.cpu.branchPred.condPredicted|system.cpu.branchPred.BTBHits'

echo "MinorCPU"
#cat ./MinorCPU/m5out/stats.txt | grep -E 'sim_ticks|sim_insts|system.cpu.numCycles|system.cpu.cpi|system.cpu.committedInsts|host_seconds|system.cpu.fetch.Insts'
cat ./MinorCPU/m5out/stats.txt | grep -E 'sim_ticks|sim_insts|system.cpu.numCycles|system.cpu.cpi|system.cpu.committedInsts|host_seconds|system.cpu.fetch.Insts|system.cpu.branchPred.condIncorrect|system.cpu.branchPred.condPredicted|system.cpu.branchPred.BTBHits'

echo "DerivO3CPU"
#cat ./DerivO3CPU/m5out/stats.txt | grep -E 'sim_ticks|sim_insts|system.cpu.numCycles|system.cpu.cpi|system.cpu.committedInsts|host_seconds|system.cpu.fetch.Insts'
cat ./DerivO3CPU/m5out/stats.txt | grep -E 'sim_ticks|sim_insts|system.cpu.numCycles|system.cpu.cpi|system.cpu.committedInsts|host_seconds|system.cpu.fetch.Insts|system.cpu.branchPred.condIncorrect|system.cpu.branchPred.condPredicted|system.cpu.branchPred.BTBHits'
