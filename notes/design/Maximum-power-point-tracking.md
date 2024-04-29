# Maximum Power Point Tracking (MPPT)
MPPT, or Maximum Power Point Tracking, is a technique used in solar inverters and chargers to extract the maximum power from a solar panel or array. Depending on how much power you are drawinf from a generator, the voltage changes. This means there exists a maximum at which you can draw the maximum power. Take a look at this example:

![An example of a power curve from a potential generator.](https://upload.wikimedia.org/wikipedia/commons/5/5a/UP-curve_of_partially_shaded_solar_generator.png)

As you can clearly see, there is a maximum at which you can draw the maximum amount of power from the generator.

To find this optimum, you'll need to measure both the voltage and current from the generator as those multiplied together give you the power buget. Once you have the voltage and current readings, you can calculate the power using the formula: 

$$
P = V \times I \text{, where }P\text{ is Power, }V\text{ is Voltage, and }I\text{ is Current.}
$$

By increasing the duty cycle you can see if you can get more power out of the generator. This is a sketch of what it'd look like:
```C
#define EVER                 true
#define INITIAL_DUTY_CYCLE   0.5f
#define DUTY_CYCLE_STEP_SIZE 0.01f

/**
 * Gets the current powerdraw based on a certain duty cycle.
 */
float getPowerUsing(const float dutyCycle) {

    setDutyCycle(dutyCycle);

    const float voltage = readVoltage();
    const float current = readCurrent();
    const float power   = ( voltage * current );

    return power;
}

/** Represents the current duty cycle that boost converter is running on. */
float currentDutyCycle = INITIAL_DUTY_CYCLE;

/** Represents the step size of the duty cycle that boost converter is changing with. */
float stepSize = DUTY_CYCLE_STEP_SIZE;

/**
 * Updates the MPPT to the better duty cycle.
 */
void maintain_MPPT() {
    
    const float oldDutyCycle = (currentDutyCycle);
    const float newDutyCycle = (oldDutyCycle + stepSize);
    
    const float powerWithOldDutyCycle = getPowerUsing(oldDutyCycle);
    const float powerWithNewDutyCycle = getPowerUsing(newDutyCycle);

    const bool powerBugetIncreased = (powerWithNewDutyCycle > powerWithOldDutyCycle);
    const bool powerBugetDecreased = (powerWithNewDutyCycle < powerWithOldDutyCycle);

    const float optimumDutyCycle;
    /* Determine the optimum Duty Cycle. */ {
        if (powerBugetIncreased) optimumDutyCycle = (newDutyCycle);
        else if (powerBugetDecreased) optimumDutyCycle = (oldDutyCycle);
        else optimumDutyCycle = (currentDutyCycle);
    }

    currentDutyCycle = (optimumDutyCycle);
    setDutyCycle(optimumDutyCycle);

    /* Changing direction if we were getting further away. */ {
        if (powerBugetDecreased) stepSize = -stepSize;
    }
}

for (;EVER;) maintain_MPPT(); // infinite loop
```

This code would maintain the MPPT.


