function getPowerMeterValue(s,event,test_meter)
global power_reading
global powerUnits

n = (s.NumScansAcquired./s.ScansAvailableFcnCount);
test_meter.updateReading(0);
power_reading(n) = test_meter.meterPowerReading;
powerUnits{n} = test_meter.meterPowerUnit;

end
