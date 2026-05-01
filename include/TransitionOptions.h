#pragma once

namespace DOTNET_NAMESPACE
{
    /// <summary>
    /// Options that control the timing of transitions between style property values.
    /// </summary>
    public ref class TransitionOptions
    {
    public:
        /// <summary>
        /// Duration of the transition in milliseconds.
        /// Null means no explicit duration (the default will apply).
        /// </summary>
        property System::Nullable<System::Int64> DurationMilliseconds;

        /// <summary>
        /// Delay before the transition starts, in milliseconds.
        /// Null means no explicit delay.
        /// </summary>
        property System::Nullable<System::Int64> DelayMilliseconds;

        /// <summary>
        /// Whether placement transitions (symbol fade-in/out) are enabled.
        /// Defaults to true.
        /// </summary>
        property System::Boolean EnablePlacementTransitions;

        TransitionOptions()
            : EnablePlacementTransitions(true) {}

        TransitionOptions(System::Nullable<System::Int64> durationMs,
                          System::Nullable<System::Int64> delayMs,
                          System::Boolean enablePlacementTransitions)
            : DurationMilliseconds(durationMs),
              DelayMilliseconds(delayMs),
              EnablePlacementTransitions(enablePlacementTransitions) {}
    };
}
