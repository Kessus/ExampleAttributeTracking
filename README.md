# ExampleAttributeTracking
<strong>Attribute Tracking System</strong> example for Unreal Engine with the Gameplay Abilities plugin.

<h3>Attribute Tracking Manager</h3>
Attribute Tracking Manager is the main point of interaction with this system. It's preferably added to the Ability System Component itself or its owner. It utilizes Tracking Directives to allow automatic responses to any fitting attribute changes. It can also process simple querries such as "Has the attribute changed at all?" or "How big was the change?".

<h3>Attribute Tracking Directives</h3>
Attribute Tracking Directives are ways of encapsulating Conditions and Responses that link them with desired Attributes. A given example directive could be understood as "If the player's stamina was used (lowered) within the last 2 seconds, apply a specific tag to the player character". Directives should be created using the provided Attribute Tracking Directive Builder using its three methods - ForAttribute, UnderCondition and AddTrackingResponse.<br><br>
<strong>IMPORTANT!! BuildDirective must be called before applying any Directive to the Manager.</strong> It can either be added to each Directive's Init method or called somewhere else for automation. 

<h3>Attribute Tracking Conditions</h3>
Attribute Tracking Conditions use the ChangeFitsCondition method to apply their logic to any change instances that they are given. The provided Basic Attribute Tracking Condition can be understood as "If the change happened recently enough, was positive/negative as requested and had a high enough value, then it fits".

<h3>Attribute Tracking Responses</h3>
<p>Attribute Tracking Responses have three distinct states they can be in: Begin, Update and End.</p>
<p><strong>Begin</strong> gets called when the response should be started and initiates the actions that it's supposed to do - in Attribute Tracking Tag Response it's applying a replicated tag.</p>
<p><strong>Update</strong> gets called each time a tracked value changes (Stamina still has changed but right now by 15 points instead of just 5) and handles refreshing any changes made eg. increasing health regeneration if even more damage was taken in the past 5 seconds.</p>
<p><strong>End</strong> gets called when the response should end and revert the changes it has made - in Attribute Tracking Tag Response it's removing the added replicated tag.</p>

<h3>Attribute Tracking Database</h3>
Attribute Tracking Database is the one that actually stores and processes all registered changes. Any new functionalities regarding change processing or querries should be implemented here and exposed in the Attribute Tracking Manager.